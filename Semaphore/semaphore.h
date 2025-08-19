#pragma once
#include <mutex>
#include <exception>
#include <condition_variable>

template <size_t MAX>
class Semaphore
{
public:
    void release(size_t update = 1)
    {
        if (update > max_counter - current_counter)
        {
            throw std::out_of_range("Error: cannot release more than max");
        }
        std::lock_guard<std::mutex> lock(mtx);
        current_counter += update;
        cv.notify_all();
    }

    void acquire()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]()
                { return current_counter > 0; });
        current_counter -= 1;
    }

    bool try_acquire()
    {
        std::lock_guard lock(mtx);
        if (current_counter == 0)
        {
            return false;
        }
        current_counter -= 1;
        return true;
    }

    size_t max() const noexcept
    {
        return max_counter;
    }

public:
    Semaphore(size_t desired) : max_counter{MAX}, current_counter{desired}
    {
        if (desired > max_counter)
        {
            throw std::out_of_range("Error: desired cannot be greater than max");
        }
    }

    Semaphore(const Semaphore &) = delete;
    Semaphore &operator=(const Semaphore &) = delete;

private:
    std::mutex mtx;
    std::condition_variable cv;
    const size_t max_counter;
    size_t current_counter;
};
