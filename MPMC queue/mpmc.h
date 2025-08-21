#pragma once
#include <queue>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <exception>

template <typename T>
class MPMCQueue
{
    using time = std::chrono::milliseconds;

    // observers
public:
    T front()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.front();
    }

    T back()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.back();
    }

    size_t max_capacity()
    {
        return capacity;
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    // modifiers
public:
    void push(const T &value)
    {
       

        std::unique_lock<std::mutex> lock(mtx);
        cv_push.wait(lock, [this]()
                     { return closed || queue.size() < capacity; });
        if (closed)
        {
            return;
        }
        queue.push(value);
        cv_pop.notify_one();
    }

    void pop()
    {
        if (capacity == 0)
        {
            return;
        }

        std::unique_lock<std::mutex> lock(mtx);
        cv_pop.wait(lock, [this]()
                    { return !queue.empty(); });
        queue.pop();
        cv_push.notify_one();
    }

    bool push_for(const T &value, time timeout_ms)
    {
        

        std::unique_lock<std::mutex> lock(mtx);
        if (cv_push.wait_for(lock, timeout_ms, [this]()
                             { return closed || queue.size() < capacity; }))
        {
            if (closed)
            {
                return false;
            }
            queue.push(value);
            cv_pop.notify_one();
            return true;
        }
        return false;
    }

    bool pop_for(time timeout_ms)
    {
       

        std::unique_lock<std::mutex> lock(mtx);
        if (cv_pop.wait_for(lock, timeout_ms, [this]()
                            { return !queue.empty(); }))
        {
            queue.pop();
            cv_push.notify_one();
            return true;
        }
        return false;
    }

    bool try_push(const T &value)
    {
        

        std::lock_guard<std::mutex> lock(mtx);
        if (closed)
        {
            return false;
        }

        if (queue.size() < capacity)
        {
            queue.push(value);
            cv_pop.notify_one();
            return true;
        }
        return false;
    }

    bool try_pop()
    {
        

        std::lock_guard<std::mutex> lock(mtx);
        if (!queue.empty())
        {
            queue.pop();
            cv_push.notify_one();
            return true;
        }
        return false;
    }

    void close()
    {
        std::lock_guard<std::mutex> lock(mtx);
        closed = true;
        cv_push.notify_all();
        cv_pop.notify_all();
    }

public:
    MPMCQueue(size_t c) : capacity{c}, closed{false} {
        if (capacity == 0)
        {
            throw std::invalid_argument("Error: capacity cannnot be 0");
        }
    }

private:
    std::mutex mtx;
    std::condition_variable cv_push;
    std::condition_variable cv_pop;
    std::queue<T> queue;
    bool closed;
    const size_t capacity;
};
