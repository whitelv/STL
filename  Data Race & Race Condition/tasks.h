#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <unordered_map>

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

template <typename T>
void partialSumWithLock(int &s, T begin, T end)
{
    int l_sum = sum(begin, end);
    mtx.lock();
    s += l_sum;
    mtx.unlock();
}

int parallelSumSingleThread(const std::vector<int> &vec)
{
    if (vec.empty())
    {
        return 0;
    }

    int s = 0;
    std::thread t([&]()
                  { s = sum(vec.cbegin(), vec.cend()); });

    t.join();
    return s;
}

int parallelSumTwoThreads(const std::vector<int> &vec)
{
    if (vec.empty())
    {
        return 0;
    }

    if (2 > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    size_t middle = std::ceil(vec.size() / 2);
    int s = 0;

    std::thread t1(partialSumWithLock<decltype(vec.cbegin())>, std::ref(s), vec.cbegin(), vec.cbegin() + middle);
    std::thread t2(partialSumWithLock<decltype(vec.cbegin())>, std::ref(s), vec.cbegin() + middle, vec.cend());

    t1.join();
    t2.join();

    return s;
}

int parallelSumNThreads(const std::vector<int> &vec, size_t t)
{
    if (vec.empty() || t == 0)
    {
        return 0;
    }

    if (t > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    size_t step = vec.size() / t;
    std::vector<std::thread> threads;
    int s = 0;

    auto curr_begin = vec.cbegin();
    auto curr_end = vec.cbegin() + step;

    for (size_t i = 0; i < t; i++)
    {
        std::thread thread(partialSumWithLock<decltype(vec.cbegin())>, std::ref(s), curr_begin, curr_end);
        threads.push_back(std::move(thread));
        curr_begin = curr_end;
        curr_end = (i + 1 == t - 1) ? vec.cend() : curr_begin + step;
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
    return s;
}

void task1(const std::vector<int> &v, size_t t)
{
    std::cout << "Single Thread:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "sum = " << parallelSumSingleThread(v) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "2 Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    std::cout << "sum = " << parallelSumTwoThreads(v) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << t << " Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    std::cout << "sum = " << parallelSumNThreads(v, t) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;
}

// Task 2 — Parallel Count of a Target Value
template <typename T>
size_t linearSearch(T begin, T end, int target)
{
    if (begin == end)
    {
        return 0;
    }
    size_t counter = 0;
    while (begin != end)
    {
        if (*begin == target)
        {
            counter++;
        }
        begin++;
    }
    return counter;
}

template <typename T>
void partialLinearSearchWithLock(size_t &count, T begin, T end, int target)
{
    size_t local_count = linearSearch(begin, end, target);
    mtx.lock();
    count += local_count;
    mtx.unlock();
}

size_t parallelCountSingleThread(const std::vector<int> &vec, int target)
{
    if (vec.empty())
    {
        return 0;
    }
    size_t count = 0;
    std::thread t([&]()
                  { count = linearSearch(vec.cbegin(), vec.cend(), target); });
    t.join();
    return count;
}

size_t parallelCountTwoThreads(const std::vector<int> &vec, int target)
{
    if (vec.empty())
    {
        return 0;
    }
    if (2 > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }
    size_t middle = std::ceil(vec.size() / 2);
    size_t count = 0;

    std::thread t1(partialLinearSearchWithLock<decltype(vec.cbegin())>, std::ref(count), vec.cbegin(), vec.cbegin() + middle, target);
    std::thread t2(partialLinearSearchWithLock<decltype(vec.cbegin())>, std::ref(count), vec.cbegin() + middle, vec.cend(), target);

    t1.join();
    t2.join();

    return count;
}

size_t parallelCountNThreads(const std::vector<int> &vec, size_t t, int target)
{
    if (vec.empty())
    {
        return 0;
    }
    if (t > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    size_t step = vec.size() / t;
    std::vector<std::thread> threads;
    size_t count = 0;

    auto curr_begin = vec.cbegin();
    auto curr_end = vec.cbegin() + step;

    for (size_t i = 0; i < t; i++)
    {
        std::thread thread(partialLinearSearchWithLock<decltype(vec.cbegin())>, std::ref(count), curr_begin, curr_end, target);
        threads.push_back(std::move(thread));
        curr_begin = curr_end;
        curr_end = (i + 1 == t - 1) ? vec.cend() : curr_begin + step;
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
    return count;
}

void task2(const std::vector<int> &v, size_t t, int target)
{
    std::cout << "Single Thread:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "count = " << parallelCountSingleThread(v, target) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "2 Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    std::cout << "count = " << parallelCountTwoThreads(v, target) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "N Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    std::cout << "count = " << parallelCountNThreads(v, t, target) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;
}

// Task 3 — Parallel Array Fill
void display_vec(const std::vector<int> &vec)
{
    for (auto &x : vec)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void fillVector(T begin, T end, size_t start_index)
{
    if (begin == end)
    {
        return;
    }
    while (begin != end)
    {
        *begin = start_index * 2;
        begin++;
        start_index++;
    }
}

std::vector<int> parallelFillSingleThread(size_t n)
{
    if (n == 0)
    {
        return std::vector<int>{};
    }

    std::vector<int> vec(n);
    std::thread t(fillVector<decltype(vec.begin())>, vec.begin(), vec.end(), 0);
    t.join();

    return vec;
}

std::vector<int> parallelFillTwoThreads(size_t n)
{
    if (n == 0)
    {
        return std::vector<int>{};
    }
    if (2 > n)
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    std::vector<int> vec(n);
    size_t middle = std::ceil(n / 2);

    std::thread t1(fillVector<decltype(vec.begin())>, vec.begin(), vec.begin() + middle, 0);
    std::thread t2(fillVector<decltype(vec.begin())>, vec.begin() + middle, vec.end(), middle);

    t1.join();
    t2.join();

    return vec;
}

std::vector<int> parallelFillNThreads(size_t t, size_t n)
{
    if (n == 0)
    {
        return std::vector<int>{};
    }
    if (t > n)
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    std::vector<int> vec(n);
    size_t step = n / t;

    std::vector<std::thread> threads;
    auto curr_begin = vec.begin();
    auto curr_end = vec.begin() + step;
    size_t start_index = 0;

    for (size_t i = 0; i < t; i++)
    {
        std::thread thread(fillVector<decltype(vec.begin())>, curr_begin, curr_end, start_index);
        threads.push_back(std::move(thread));
        start_index += curr_end - curr_begin;
        curr_begin = curr_end;
        curr_end = (i + 1 == t - 1) ? vec.end() : curr_begin + step;
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    return vec;
}

void task3(size_t t, size_t n)
{
    std::cout << "Single Thread:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    display_vec(parallelFillSingleThread(n));
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "2 Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    display_vec(parallelFillTwoThreads(n));
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "N Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    display_vec(parallelFillNThreads(t, n));
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;
}

// Task 4 — Parallel Histogram (Alphabet 0..10)

void display_histogram(const std::unordered_map<uint8_t, size_t> &histogram)
{
    auto begin = histogram.cbegin();
    while (begin != histogram.cend())
    {
        std::cout << "H[" << unsigned(begin->first) << "] = " << begin->second << ", ";
        begin++;
    }
    std::cout << std::endl;
}

template <typename T>
std::unordered_map<uint8_t, size_t> createHistogram(T begin, T end)
{
    if (begin == end)
    {
        return std::unordered_map<uint8_t, size_t>{};
    }

    std::unordered_map<uint8_t, size_t> histogram;

    while (begin != end)
    {
        histogram[*begin]++;
        begin++;
    }
    return histogram;
}

template <typename T>
void updateHistogram(std::unordered_map<uint8_t, size_t> &histogram, T begin, T end)
{
    auto local_histogrma = createHistogram(begin, end);
    auto local_begin = local_histogrma.cbegin();
    mtx.lock();
    while (local_begin != local_histogrma.cend())
    {
        histogram[local_begin->first] += local_begin->second;
        local_begin++;
    }
    mtx.unlock();
}

std::unordered_map<uint8_t, size_t> parallelHistogramSingleThread(const std::vector<uint8_t> &vec)
{
    if (vec.empty())
    {
        return std::unordered_map<uint8_t, size_t>{};
    }
    std::unordered_map<uint8_t, size_t> histogram;
    std::thread t([&]()
                  { histogram = createHistogram(vec.cbegin(), vec.cend()); });
    t.join();
    return histogram;
}

std::unordered_map<uint8_t, size_t> parallelHistogramTwoThreads(const std::vector<uint8_t> &vec)
{
    if (vec.empty())
    {
        return std::unordered_map<uint8_t, size_t>{};
    }
    if (2 > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    size_t middle = std::ceil(vec.size() / 2);
    std::unordered_map<uint8_t, size_t> histogram;

    std::thread t1(updateHistogram<decltype(vec.cbegin())>, std::ref(histogram), vec.cbegin(), vec.cbegin() + middle);
    std::thread t2(updateHistogram<decltype(vec.cbegin())>, std::ref(histogram), vec.cbegin() + middle, vec.cend());

    t1.join();
    t2.join();

    return histogram;
}

std::unordered_map<uint8_t, size_t> parallelHistogramNThreads(const std::vector<uint8_t> &vec, size_t t)
{
    if (vec.empty())
    {
        return std::unordered_map<uint8_t, size_t>{};
    }
    if (t > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    size_t step = vec.size() / t;
    std::unordered_map<uint8_t, size_t> histogram;

    std::vector<std::thread> threads;
    auto curr_begin = vec.cbegin();
    auto curr_end = vec.cbegin() + step;

    for (size_t i = 0; i < t; i++)
    {
        std::thread thread(updateHistogram<decltype(vec.begin())>, std::ref(histogram), curr_begin, curr_end);
        threads.push_back(std::move(thread));
        curr_begin = curr_end;
        curr_end = (i + 1 == t - 1) ? vec.cend() : curr_begin + step;
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
    return histogram;
}

void task4(const std::vector<uint8_t> &vec, size_t t)
{
    std::cout << "Single Thread:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    display_histogram(parallelHistogramSingleThread(vec));
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "2 Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    display_histogram(parallelHistogramTwoThreads(vec));
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "N Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    display_histogram(parallelHistogramNThreads(vec, t));
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;
}

// Task 5 — Parallel Max Element with Lowest Index

void display_pair(const std::pair<int, size_t> &pair)
{
    std::cout << "[" << pair.first << " : " << pair.second << "]" << std::endl;
}

template <typename T>
std::pair<int, size_t> findMax(T begin, T end, size_t start_index)
{
    if (begin == end)
    {
        return {-1, ULONG_MAX};
    }

    std::pair<int, size_t> max = {*begin++, start_index++};

    size_t i = start_index;
    while (begin != end)
    {
        if (*begin > max.first)
        {
            max = {*begin, i};
        }
        begin++;
        i++;
    }

    return max;
}

template <typename T>
void savePartialMax(std::vector<std::pair<int, size_t>> &vec, T begin, T end, size_t start_index)
{
    auto max = findMax(begin, end, start_index);
    mtx.lock();
    vec.push_back(std::move(max));
    mtx.unlock();
}

std::pair<int, size_t> parallelMaxElementLowestIndexSingleThread(const std::vector<int> &vec)
{
    if (vec.empty())
    {
        return {-1, ULONG_MAX};
    }

    std::pair<int, size_t> max;
    std::thread t([&]()
                  { max = findMax(vec.cbegin(), vec.cend(), 0); });

    t.join();

    return max;
}

std::pair<int, size_t> parallelMaxElementLowestIndexTwoThreads(const std::vector<int> &vec)
{
    if (vec.empty())
    {
        return {-1, ULONG_MAX};
    }
    if (2 > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    size_t middle = std::ceil(vec.size() / 2);
    std::vector<std::pair<int, size_t>> partialMaxes;

    std::thread t1(savePartialMax<decltype(vec.cbegin())>, std::ref(partialMaxes), vec.cbegin(), vec.cbegin() + middle, 0);
    std::thread t2(savePartialMax<decltype(vec.cbegin())>, std::ref(partialMaxes), vec.cbegin() + middle, vec.cend(), middle);

    t1.join();
    t2.join();

    return partialMaxes[0].first >= partialMaxes[1].first && partialMaxes[0].second < partialMaxes[1].second ? partialMaxes[0] : partialMaxes[1];
}

std::pair<int, size_t> parallelMaxElementLowestIndexNThreads(const std::vector<int> &vec, size_t t)
{
    if (vec.empty())
    {
        return {-1, ULONG_MAX};
    }
    if (t > vec.size())
    {
        throw std::invalid_argument("Error: cannot have more threads than values in vector");
    }

    size_t step = vec.size() / t;
    std::vector<std::pair<int, size_t>> partialMaxes;

    std::vector<std::thread> threads;
    auto curr_begin = vec.cbegin();
    auto curr_end = vec.cbegin() + step;
    size_t start_index = 0;

    for (size_t i = 0; i < t; i++)
    {
        std::thread thread(savePartialMax<decltype(vec.cbegin())>, std::ref(partialMaxes), curr_begin, curr_end, start_index);
        threads.push_back(std::move(thread));
        start_index += curr_end - curr_begin;
        curr_begin = curr_end;
        curr_end = (i + 1 == t - 1) ? vec.end() : curr_begin + step;
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    auto begin = partialMaxes.begin();

    std::pair<int, size_t> max = *begin++;

    while (begin != partialMaxes.end())
    {
        if (begin->first > max.first || (begin->first == max.first && begin->second < max.second))
        {
            max = *begin;
        }
        begin++;
    }
    
    return max;
}