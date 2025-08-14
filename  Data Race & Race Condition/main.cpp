#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>

std::mutex mtx;

// Task 1 — Parallel Sum
template <typename T>
int sum(T begin, T end)
{
    if (begin == end)
    {
        return 0;
    }

    int s = 0;
    while (begin != end)
    {
        s += *begin;
        begin++;
    }
    return s;
}

int parallelSumSingleThread(std::vector<int> vec)
{
    if (vec.empty())
    {
        return 0;
    }

    int s = 0;
    std::thread t([&]()
                  { s = sum(vec.begin(), vec.end()); });

    t.join();
    return s;
}

template <typename T>
void partialSumWithLock(int &s, T begin, T end)
{
    int l_sum = sum(begin, end);
    mtx.lock();
    s += l_sum;
    mtx.unlock();
}

int parallelSumTwoThreads(std::vector<int> vec)
{
    if (vec.empty())
    {
        return 0;
    }
    size_t middle = std::ceil(vec.size() / 2);
    int s = 0;

    std::thread t1(partialSumWithLock<decltype(vec.begin())>, std::ref(s), vec.begin(), vec.begin() + middle);
    std::thread t2(partialSumWithLock<decltype(vec.begin())>, std::ref(s), vec.begin() + middle, vec.end());

    t1.join();
    t2.join();

    return s;
}

int parallelSumNThreads(std::vector<int> vec, size_t t)
{
    if (vec.empty() || t == 0)
    {
        return 0;
    }
    size_t step = vec.size() / t;
    std::vector<std::thread> threads;
    int s = 0;

    auto curr_begin = vec.begin();
    auto curr_end = vec.begin() + step;

    for (size_t i = 0; i < t; i++)
    {
        std::thread thread(partialSumWithLock<decltype(vec.begin())>, std::ref(s), curr_begin, curr_end);
        threads.push_back(std::move(thread));
        curr_begin = curr_end;
        curr_end = (i + 1 == t - 1) ? vec.end() : curr_begin + step;
    }

    for(auto &thread : threads){
        thread.join();
    }
    return s;
}

int main()
{
    std::vector<int> v(100, 1);
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "sum = " << parallelSumSingleThread(v) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::cout << "sum = " << parallelSumTwoThreads(v) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::cout << "sum = " << parallelSumNThreads(v, 2) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;
}