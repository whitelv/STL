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

private:
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

public:
    bool post(size_t id, std::function<void()> func, std::chrono::time_point<clock> run_at);
    bool cancel(size_t id);
    void shutdown(bool cancel = false);



private:
    void schedule();
    void work();

public:
    Scheduler() : is_shutdown(false), new_point(std::chrono::time_point<clock>::max()), current_point(std::chrono::time_point<clock>::max()),
                  scheduler_thread{std::thread([this]
                                               { schedule(); })},
                  worker_thread{std::thread([this]
                                            { work(); })}
    {
    }
    ~Scheduler();

public:
    std::mutex mtx;
    std::condition_variable cv_scheduler;
    std::condition_variable cv_worker;

    std::vector<task_heap> tasks_heap;
    std::unordered_map<size_t, task_map> tasks_map;
    std::queue<task_map> tasks_queue;

    bool is_shutdown;

    std::chrono::time_point<clock> new_point;
    std::chrono::time_point<clock> current_point;

    std::thread scheduler_thread;
    std::thread worker_thread;
};