#include "tasks.h"
#include <random>
#include <algorithm>

int main()
{
    std::vector<int> vec;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 100000);

    for (size_t i = 0; i < 10000000; i++)
    {
        vec.push_back(distrib(gen));
    }

    std::cout << "Single Thread:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    display_pair(parallelMaxElementLowestIndexSingleThread(vec));
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "2 Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    display_pair(parallelMaxElementLowestIndexTwoThreads(vec));
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;

    std::cout << "N Threads:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    display_pair(parallelMaxElementLowestIndexNThreads(vec, 4));
    stop = std::chrono::high_resolution_clock::now();
    duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration = " << duration << std::endl;
}