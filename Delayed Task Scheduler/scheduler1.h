#pragma once
#include <mutex>
#include <thread>
#include <queue>
#include <iostream>
#include <condition_variable>
#include <chrono>
#include <functional>
#include <unordered_map>

class Scheduler
{
public:
    using clock = std::chrono::high_resolution_clock;
    struct task_heap
    {
        size_t id;
        std::chrono::time_point<clock> run_at;
        friend bool operator>(const task_heap &t1, const task_heap &t2)
        {
            return t1.run_at > t2.run_at;
        }
    };

    struct task_map
    {
        std::function<void()> func;
        std::chrono::time_point<clock> run_at;
    };

    bool post(size_t id, std::function<void()> func, std::chrono::time_point<clock> run_at)
    {
        if (is_shutdown || tasks_map.contains(id))
        {
            return false;
        }
        
        std::lock_guard<std::mutex> lock(mtx);
        // std::cout << "post" << std::endl;
        tasks_heap.push_back(task_heap{id, run_at});
        std::push_heap(tasks_heap.begin(), tasks_heap.end(), std::greater());
        tasks_map[id] = task_map{func, run_at};
        new_point = tasks_heap[0].run_at;
        cv_scheduler.notify_one();

        return true;
    }

    void schedule()
    {
        while (true)
        {

            std::unique_lock<std::mutex> lock(mtx);
            // std::cout << "scheduler thread started" << std::endl;
            while (true)
            {
                bool ok = cv_scheduler.wait_until(lock, current_point, [this]()
                                                  { return is_shutdown || current_point != new_point; });

                // iterations++;

                if (is_shutdown)
                {
                    // std::cout << "scheduler thread shutdown" << std::endl;
                    return;
                }

                // std::cout << "heap is not empty" << std::endl;

                // std::cout << "current point before change: " << current_point << std::endl;
                if (current_point != new_point)
                {
                    current_point = new_point;
                }
                // std::cout << "current point after change: " << current_point << std::endl;

                if (clock::now() > current_point)
                {
                    // std::cout << "clock::now() > current_point" << std::endl;
                    break;
                }
            }
            auto id = tasks_heap[0].id;

            tasks_queue.push(tasks_map[id]);
            tasks_map.erase(id);
            std::pop_heap(tasks_heap.begin(), tasks_heap.end(), std::greater());
            tasks_heap.pop_back();
            // std::cout << "tasks_heap.size() = " << tasks_heap.size() << std::endl;
            // std::cout << "deletion time= " << clock::now() << std::endl;
            current_point = new_point = tasks_heap.empty() ? std::chrono::time_point<clock>::max() : tasks_heap[0].run_at;
            cv_worker.notify_one();
            // std::cout << "scheduler thread finished" << std::endl;
        }
    }

    void work()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(mtx);
            // std::cout << "worker thread started" << std::endl;
            cv_worker.wait(lock, [this]()
                           { return is_shutdown || !tasks_queue.empty(); });

            if (is_shutdown)
            {
                // std::cout << "worker thread shutdown" << std::endl;
                while (!tasks_queue.empty())
                {
                    auto task = tasks_queue.front();
                    tasks_queue.pop();
                    std::cout << "actual time = " << clock::now() << " task time = " << task.run_at << std::endl;
                    std::cout << "time diff = " << clock::now() - task.run_at << std::endl;
                    task.func();
                    iterations++;
                }
                return;
            }

            auto task = tasks_queue.front();
            tasks_queue.pop();

            // std::cout << "start doing task" << std::endl;
            std::cout << "actual time = " << clock::now() << " task time = " << task.run_at << std::endl;
            std::cout << "time diff = " << clock::now() - task.run_at << std::endl;
            task.func();
            iterations++;
            // std::cout << "finish doing task" << std::endl;

            // std::cout << "worker thread finished" << std::endl;
        }
    }

    

    Scheduler() : is_shutdown(false), new_point(std::chrono::time_point<clock>::max()), current_point(std::chrono::time_point<clock>::max())
    {
        // std::cout << "constructor" << std::endl;

        scheduler_thread = std::thread([this]
                                       { schedule(); });

        worker_thread = std::thread([this]
                                    { work(); });
    }

    void shutdown(bool cancel = false)
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

    ~Scheduler()
    {
        // std::cout << "destructor" << std::endl;
        // std::cout << "iterations" << iterations << std::endl;

        // {
        //     std::lock_guard<std::mutex> lock(mtx);
        //     while (!tasks_queue.empty())
        //     {
        //         std::cout << tasks_queue.front().run_at << std::endl;
        //         tasks_queue.pop();
        //     }

        //     size_t i = 0;
        //     while (!tasks_heap.empty())
        //     {
        //         std::cout << tasks_heap[0].run_at << std::endl;

        //         std::pop_heap(tasks_heap.begin(), tasks_heap.end(), std::greater());
        //         tasks_heap.pop_back();
        //     }
        //     is_shutdown = true;
        //     cv_scheduler.notify_one();
        //     cv_worker.notify_one();
        // }
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
        // std::cout << "iterations" << iterations << std::endl;

    }

public:
    std::mutex mtx;
    std::condition_variable cv_scheduler;
    std::condition_variable cv_worker;

    std::vector<task_heap> tasks_heap;
    std::unordered_map<size_t, task_map> tasks_map;
    std::queue<task_map> tasks_queue;

    bool is_shutdown;

    std::thread scheduler_thread;
    std::thread worker_thread;

    std::chrono::time_point<clock> new_point;
    std::chrono::time_point<clock> current_point;

    size_t iterations = 0;
};