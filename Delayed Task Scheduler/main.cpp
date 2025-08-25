#include "scheduler.h"

std::mutex mtx;
std::condition_variable cv;

using timepoint = std::chrono::time_point<Scheduler::clock>;
using ms = std::chrono::milliseconds;

auto time1 = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(5000);

void push_time(std::vector<timepoint> &vec, size_t size)
{
        vec.push_back(std::chrono::high_resolution_clock::now());
        std::unique_lock<std::mutex> lock(mtx);
        if (vec.size() == size)
        {
                cv.notify_one();
        }
}

bool check_execution_time(const std::vector<timepoint> &vec)
{
        auto it_first = vec.cbegin();
        auto it_second = ++vec.cbegin();

        while (it_second != vec.cend())
        {
                if (*it_first > *it_second)
                {
                        return false;
                }

                it_first++;
                it_second++;
        }
        return true;
}

int main()
{

        return 0;
}
