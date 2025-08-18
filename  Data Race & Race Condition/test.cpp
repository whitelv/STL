#include "gtest/gtest.h"
#include "tasks.h"
#include <random>
#include <numeric>
#include <algorithm>

// Task 1
TEST(ThreadSumModule, CalculateSumWithEmptyVector)
{
    std::vector<int> v;
    EXPECT_EQ(parallelSumSingleThread(v), 0);
    EXPECT_EQ(parallelSumTwoThreads(v), 0);
    EXPECT_EQ(parallelSumNThreads(v, 4), 0);
}

TEST(ThreadSumModule, CalculateSumWithOneValueVector)
{
    std::vector<int> v{1};
    EXPECT_EQ(parallelSumSingleThread(v), 1);
    EXPECT_THROW(parallelSumTwoThreads(v), std::invalid_argument);
    EXPECT_THROW(parallelSumNThreads(v, 4), std::invalid_argument);
}

TEST(ThreadSumModule, CalculateSumWithSmallVector)
{

    std::vector<int> v = {1, 0, 4, 3, 2, 10};
    long long sum = 20;
    EXPECT_EQ(parallelSumSingleThread(v), sum);
    EXPECT_EQ(parallelSumTwoThreads(v), sum);
    EXPECT_EQ(parallelSumNThreads(v, 4), sum);
}

TEST(ThreadSumModule, CalculateSumWithEqualSizeAndThreadsVector)
{

    std::vector<int> v = {10, 10, 10, 10};
    EXPECT_EQ(parallelSumNThreads(v, 4), 40);
}

TEST(ThreadSumModule, CalculateSumWithRandomVector)
{
    std::vector<int> v;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 10);

    for (size_t i = 0; i < 1000000; i++)
    {
        v.push_back(distrib(gen));
    }

    long long sum = std::accumulate(v.begin(), v.end(), 0);

    EXPECT_EQ(parallelSumSingleThread(v), sum);
    EXPECT_EQ(parallelSumTwoThreads(v), sum);
    EXPECT_EQ(parallelSumNThreads(v, 3), sum);
    EXPECT_EQ(parallelSumNThreads(v, 4), sum);
    EXPECT_EQ(parallelSumNThreads(v, 8), sum);
}

// Task 2
TEST(ThreadCountModule, CalculateCountWithEmptyVector)
{
    std::vector<int> v;
    EXPECT_EQ(parallelCountSingleThread(v, 0), 0);
    EXPECT_EQ(parallelCountTwoThreads(v, 0), 0);
    EXPECT_EQ(parallelCountNThreads(v, 4, 0), 0);
}

TEST(ThreadCountModule, CalculateCountWithOneValueVector)
{
    std::vector<int> v{1};
    EXPECT_EQ(parallelCountSingleThread(v, 1), 1);
    EXPECT_THROW(parallelCountTwoThreads(v, 1), std::invalid_argument);
    EXPECT_THROW(parallelCountNThreads(v, 4, 1), std::invalid_argument);
}

TEST(ThreadCountModule, CalculateCountWithSmallVector)
{
    std::vector<int> v = {2, 5, 5, 1, 5, 0, 9};
    int count = std::count(v.begin(), v.end(), 5);
    EXPECT_EQ(parallelCountSingleThread(v, 5), count);
    EXPECT_EQ(parallelCountTwoThreads(v, 5), count);
    EXPECT_EQ(parallelCountNThreads(v, 3, 5), count);
}

TEST(ThreadCountModule, CalculateCountWithSameValuesVectorMatch)
{
    std::vector<int> v;
    for (size_t i = 0; i < 15; i++)
    {
        v.push_back(7);
    }
    int count = std::count(v.begin(), v.end(), 7);
    EXPECT_EQ(parallelCountSingleThread(v, 7), count);
    EXPECT_EQ(parallelCountTwoThreads(v, 7), count);
    EXPECT_EQ(parallelCountNThreads(v, 3, 7), count);
}

TEST(ThreadCountModule, CalculateCountWithSameValuesVectorNoMatch)
{
    std::vector<int> v;
    for (size_t i = 0; i < 15; i++)
    {
        v.push_back(7);
    }
    int count = std::count(v.begin(), v.end(), 5);
    EXPECT_EQ(parallelCountSingleThread(v, 5), count);
    EXPECT_EQ(parallelCountTwoThreads(v, 5), count);
    EXPECT_EQ(parallelCountNThreads(v, 3, 5), count);
}

TEST(ThreadCountModule, CalculateCountWithEqualSizeAndThreadsVector)
{

    std::vector<int> v;
    for (size_t i = 0; i < 8; i++)
    {
        v.push_back(7);
    }
    int count = std::count(v.begin(), v.end(), 7);
    EXPECT_EQ(parallelCountNThreads(v, 8, 7), count);
}

TEST(ThreadCountModule, CalculateSumWithRandomVector)
{
    std::srand(std::time(0));
    std::vector<int> v;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 10);

    for (size_t i = 0; i < 10000000; i++)
    {
        v.push_back(distrib(gen));
    }

    int count = std::count(v.begin(), v.end(), 6);

    EXPECT_EQ(parallelCountSingleThread(v, 6), count);
    EXPECT_EQ(parallelCountTwoThreads(v, 6), count);
    EXPECT_EQ(parallelCountNThreads(v, 3, 6), count);
    EXPECT_EQ(parallelCountNThreads(v, 4, 6), count);
    EXPECT_EQ(parallelCountNThreads(v, 8, 6), count);
}

// Task 3
TEST(ThreadFillModule, FillEmptyVector)
{
    std::vector<int> result;
    EXPECT_EQ(result, parallelFillSingleThread(0));
    EXPECT_EQ(result, parallelFillTwoThreads(0));
    EXPECT_EQ(result, parallelFillNThreads(3, 0));
}

TEST(ThreadFillModule, FillOneElementVector)
{
    std::vector<int> result{0};
    EXPECT_EQ(result, parallelFillSingleThread(1));
    EXPECT_THROW(parallelFillTwoThreads(1), std::invalid_argument);
    EXPECT_THROW(parallelFillNThreads(3, 1), std::invalid_argument);
}

TEST(ThreadFillModule, FillSmallVector)
{
    std::vector<int> result;
    for (size_t i = 0; i < 25; i++)
    {
        result.push_back(i * 2);
    }

    EXPECT_EQ(result, parallelFillSingleThread(25));
    EXPECT_EQ(result, parallelFillTwoThreads(25));
    EXPECT_EQ(result, parallelFillNThreads(3, 25));
}

TEST(ThreadFillModule, FillVectorWithDiffirentSizes)
{

    for (size_t i = 3; i < 15; i++)
    {
        std::vector<int> result;
        for (size_t j = 0; j < i; j++)
        {
            result.push_back(j * 2);
        }

        EXPECT_EQ(result, parallelFillSingleThread(i));
        EXPECT_EQ(result, parallelFillTwoThreads(i));
        EXPECT_EQ(result, parallelFillNThreads(3, i));
    }
}

TEST(ThreadFillModule, FillVectorWithDiffirentThreads)
{
    std::vector<int> result;
    for (size_t i = 0; i < 25; i++)
    {
        result.push_back(i * 2);
    }
    EXPECT_EQ(result, parallelFillNThreads(3, 25));
    EXPECT_EQ(result, parallelFillNThreads(4, 25));
    EXPECT_EQ(result, parallelFillNThreads(8, 25));
}

// Task 4
TEST(ThreadHistogramModule, createHistogramEmptyVector)
{
    std::vector<uint8_t> vec;
    std::unordered_map<uint8_t, size_t> result;
    EXPECT_EQ(result, parallelHistogramSingleThread(vec));
    EXPECT_EQ(result, parallelHistogramTwoThreads(vec));
    EXPECT_EQ(result, parallelHistogramNThreads(vec, 3));
}

TEST(ThreadHistogramModule, createHistogramOneValueVector)
{
    std::vector<uint8_t> vec{1};
    std::unordered_map<uint8_t, size_t> result{{1, 1}};
    EXPECT_EQ(result, parallelHistogramSingleThread(vec));
    EXPECT_THROW(parallelHistogramTwoThreads(vec), std::invalid_argument);
    EXPECT_THROW(parallelHistogramNThreads(vec, 3), std::invalid_argument);
}

TEST(ThreadHistogramModule, createHistogramOnlyUniqueValues)
{
    std::vector<uint8_t> vec;

    std::unordered_map<uint8_t, size_t> result;
    for (size_t i = 0; i < 11; i++)
    {
        vec.push_back(i);
        result[i] = 1;
    }

    EXPECT_EQ(result, parallelHistogramSingleThread(vec));
    EXPECT_EQ(result, parallelHistogramTwoThreads(vec));
    EXPECT_EQ(result, parallelHistogramNThreads(vec, 3));
}

TEST(ThreadHistogramModule, createHistogramSameValueVector)
{
    std::vector<uint8_t> vec;

    std::unordered_map<uint8_t, size_t> result;
    for (size_t i = 0; i < 11; i++)
    {
        vec.push_back(7);
        result[7] += 1;
    }

    EXPECT_EQ(result, parallelHistogramSingleThread(vec));
    EXPECT_EQ(result, parallelHistogramTwoThreads(vec));
    EXPECT_EQ(result, parallelHistogramNThreads(vec, 3));
}

TEST(ThreadHistogramModule, createHistogramRandom)
{
    std::vector<uint8_t> vec;
    std::unordered_map<uint8_t, size_t> result;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 10);

    int randomValue{};
    for (size_t i = 0; i < 1000000; i++)
    {
        randomValue = distrib(gen);
        vec.push_back(randomValue);
        result[randomValue] += 1;
    }

    EXPECT_EQ(result, parallelHistogramSingleThread(vec));
    EXPECT_EQ(result, parallelHistogramTwoThreads(vec));
    EXPECT_EQ(result, parallelHistogramNThreads(vec, 3));
    EXPECT_EQ(result, parallelHistogramNThreads(vec, 4));
    EXPECT_EQ(result, parallelHistogramNThreads(vec, 8));
}

// task 5
TEST(ThreadMaxModule, findMaxEmptyVector)
{
    std::vector<int> vec;
    std::pair<int, size_t> result = {-1, ULONG_MAX};
    EXPECT_EQ(result, parallelMaxElementLowestIndexSingleThread(vec));
    EXPECT_EQ(result, parallelMaxElementLowestIndexTwoThreads(vec));
    EXPECT_EQ(result, parallelMaxElementLowestIndexNThreads(vec, 3));
}


TEST(ThreadMaxModule, findMaxOneValueVector)
{
    std::vector<int> vec{1};
    std::pair<int, size_t> result = {1, 0};
    EXPECT_EQ(result, parallelMaxElementLowestIndexSingleThread(vec));
    EXPECT_THROW(parallelMaxElementLowestIndexTwoThreads(vec), std::invalid_argument);
    EXPECT_THROW(parallelMaxElementLowestIndexNThreads(vec, 3), std::invalid_argument);
}


TEST(ThreadMaxModule, findMaxIncreasingValuesVector)
{
    std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    std::pair<int, size_t> result = {10, 9};
    EXPECT_EQ(result, parallelMaxElementLowestIndexSingleThread(vec));
    EXPECT_EQ(result, parallelMaxElementLowestIndexTwoThreads(vec));
    EXPECT_EQ(result, parallelMaxElementLowestIndexNThreads(vec, 3));
}


TEST(ThreadMaxModule, findMaxMultipleMaxValuesVector)
{
    std::vector<int> vec{3, 10, 7, 10, 5};
    std::pair<int, size_t> result = {10, 1};
    EXPECT_EQ(result, parallelMaxElementLowestIndexSingleThread(vec));
    EXPECT_EQ(result, parallelMaxElementLowestIndexTwoThreads(vec));
    EXPECT_EQ(result, parallelMaxElementLowestIndexNThreads(vec, 3));
}


TEST(ThreadMaxModule, findMaxRandomVector)
{
    std::vector<int> vec;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 10);

    for (size_t i = 0; i < 1000000; i++)
    {
        vec.push_back(distrib(gen));
    }
    auto result1 = parallelMaxElementLowestIndexSingleThread(vec);
    auto result2 = parallelMaxElementLowestIndexTwoThreads(vec);
    auto result3 = parallelMaxElementLowestIndexNThreads(vec, 3);
    auto result4 = parallelMaxElementLowestIndexNThreads(vec, 4);
    auto result8 = parallelMaxElementLowestIndexNThreads(vec, 8);
    
    ASSERT_EQ(result1, result2);
    ASSERT_EQ(result2, result3);
    ASSERT_EQ(result3, result4);
    ASSERT_EQ(result4, result8);
}
