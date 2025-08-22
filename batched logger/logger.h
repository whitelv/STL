#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <condition_variable>

template <typename Interface>
class Logger
{
    using clock = std::chrono::high_resolution_clock;

public:
    void log(const std::string &str)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv_prod.wait(lock, [this]
                     { return stopped || buffer.size() < max_size; });

        if (stopped)
        {
            return;
        }

        buffer += str;
        if (buffer.size() >= max_size)
        {
            cv_cons.notify_one();
        }
    }

    void stop()
    {
        std::lock_guard<std::mutex> lock(mtx);
        stopped = true;
        cv_cons.notify_all();
        cv_prod.notify_all();
        interface << buffer;
        buffer.clear();
    }

private:
    void flush()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv_cons.wait_until(lock, next_hop, [this]
                           { return stopped || buffer.size() >= max_size; });
        if (stopped)
        {
            return;
        }

        interface << buffer;
        buffer.clear();
        cv_prod.notify_all();
        next_hop = calc_next_hop();
    }

    std::chrono::time_point<clock> calc_next_hop()
    {
        return clock::now() + timeout;
    }
    
    std::thread create_flush_thread()
    {
        return std::thread([this]
                           {
            while (true) {
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (stopped) {
                        break;
                    }
                }
                flush();
            } });
    }

public:
    Logger(std::chrono::milliseconds ms, size_t s, Interface &inter) : timeout{ms}, max_size{s}, stopped{false}, next_hop{calc_next_hop()}, interface{inter}
    {
        flush_thread = create_flush_thread();
    }

    ~Logger()
    {
        stop();
        flush_thread.join();
    }

private:
    const std::chrono::milliseconds timeout;
    const size_t max_size;

    Interface &interface;
    std::string buffer;
    std::chrono::time_point<clock> next_hop;
    bool stopped;

    std::mutex mtx;
    std::condition_variable cv_prod;
    std::condition_variable cv_cons;
    std::thread flush_thread;
};