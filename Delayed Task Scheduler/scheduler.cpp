#include "scheduler.h"

bool Scheduler::post(size_t id, std::function<void()> func, std::chrono::time_point<clock> run_at)
{
    if (is_shutdown || tasks_map.contains(id))
    {
        return false;
    }

    std::lock_guard<std::mutex> lock(mtx);
    tasks_heap.push_back(task_heap{id, run_at});
    std::push_heap(tasks_heap.begin(), tasks_heap.end(), std::greater());
    tasks_map[id] = task_map{func, run_at};
    new_point = tasks_heap[0].run_at;
    cv_scheduler.notify_one();

    return true;
}

void Scheduler::schedule()
{
    while (true)
    {

        std::unique_lock<std::mutex> lock(mtx);
        while (true)
        {
            bool ok = cv_scheduler.wait_until(lock, current_point, [this]()
                                              { return is_shutdown || current_point != new_point; });

            if (is_shutdown)
            {
                return;
            }

            if (current_point != new_point)
            {
                current_point = new_point;
            }

            if (clock::now() > current_point)
            {
                break;
            }
        }
        auto id = tasks_heap[0].id;

        tasks_queue.push(tasks_map[id]);
        tasks_map.erase(id);
        std::pop_heap(tasks_heap.begin(), tasks_heap.end(), std::greater());
        tasks_heap.pop_back();
        current_point = new_point = tasks_heap.empty() ? std::chrono::time_point<clock>::max() : tasks_heap[0].run_at;
        cv_worker.notify_one();
    }
}

void Scheduler::work()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv_worker.wait(lock, [this]()
                       { return is_shutdown || !tasks_queue.empty(); });

        if (is_shutdown)
        {
            while (!tasks_queue.empty())
            {
                auto task = tasks_queue.front();
                tasks_queue.pop();
                task.func();
            }
            return;
        }

        auto task = tasks_queue.front();
        tasks_queue.pop();

        task.func();
    }
}

bool Scheduler::cancel(size_t id)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (is_shutdown || !tasks_map.contains(id))
    {
        return false;
    }
    tasks_map.erase(id);
    tasks_heap.erase(std::find_if(tasks_heap.begin(), tasks_heap.end(), [&](const task_heap &t)
                                  { return t.id == id; }));
    std::make_heap(tasks_heap.begin(), tasks_heap.end(), std::greater());
    current_point = new_point = tasks_heap.empty() ? std::chrono::time_point<clock>::max() : tasks_heap[0].run_at;
    cv_scheduler.notify_one();
    return true;
}

void Scheduler::shutdown(bool cancel)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (cancel)
    {
        is_shutdown = true;
        cv_scheduler.notify_one();
        cv_worker.notify_one();
        return;
    }
    while (!tasks_heap.empty())
    {
        auto id = tasks_heap[0].id;
        tasks_queue.push(tasks_map[id]);
        tasks_map.erase(id);
        std::pop_heap(tasks_heap.begin(), tasks_heap.end(), std::greater());
        tasks_heap.pop_back();
    }
    is_shutdown = true;
    cv_scheduler.notify_one();
    cv_worker.notify_one();
}

Scheduler::~Scheduler()
{
    if (!is_shutdown)
    {
        shutdown();
    }

    if (scheduler_thread.joinable())
    {
        scheduler_thread.join();
    }
    if (worker_thread.joinable())
    {
        worker_thread.join();
    }
}