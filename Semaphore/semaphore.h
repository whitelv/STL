#pragma once
#include <mutex>
#include <exception>

template <size_t MAX>
class Semaphore
{
public:
    void release(size_t update = 1)
    {
        if (update <= max_counter - current_counter)
        {
            mtx.lock();
            current_counter += update;
            mtx.unlock();
        }
    }

    void acquire()
    {
        while (true)
        {
            mtx.lock();
            if (current_counter == 0)
            {
                mtx.unlock();
                continue;
            }
            current_counter -= 1;
            mtx.unlock();
            break;
        }
    }

    bool try_acquire()
    {
        mtx.lock();
        if (current_counter == 0)
        {
            mtx.unlock();
            return false;
        }
        current_counter -= 1;
        mtx.unlock();
        return true;
    }

    size_t max() noexcept
    {
        return max_counter;
    }

public:
    Semaphore(size_t desired) : max_counter{MAX}, current_counter{desired}
    {
        if (desired > max_counter)
        {
            throw std::out_of_range("Error: desired cannot be bigger than max");
        }
    }

    Semaphore(const Semaphore &) = delete;
    Semaphore &operator=(const Semaphore &) = delete;

private:
    std::mutex mtx;
    const size_t max_counter;
    size_t current_counter;
};
