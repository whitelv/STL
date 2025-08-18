#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <unordered_map>

extern std::mutex mtx;

// Task 1 — Parallel Sum
long long parallelSumSingleThread(const std::vector<int> &vec);
long long parallelSumTwoThreads(const std::vector<int> &vec);
long long parallelSumNThreads(const std::vector<int> &vec, size_t t);
void task1(const std::vector<int> &v, size_t t);

// Task 2 — Parallel Count of a Target Value
size_t parallelCountSingleThread(const std::vector<int> &vec, int target);
size_t parallelCountTwoThreads(const std::vector<int> &vec, int target);
size_t parallelCountNThreads(const std::vector<int> &vec, size_t t, int target);
void task2(const std::vector<int> &v, size_t t, int target);

// Task 3 — Parallel Array Fill
std::vector<int> parallelFillSingleThread(size_t n);
std::vector<int> parallelFillTwoThreads(size_t n);
std::vector<int> parallelFillNThreads(size_t t, size_t n);
void task3(size_t t, size_t n);

// Task 4 — Parallel Histogram (Alphabet 0..10)

std::unordered_map<uint8_t, size_t> parallelHistogramSingleThread(const std::vector<uint8_t> &vec);
std::unordered_map<uint8_t, size_t> parallelHistogramTwoThreads(const std::vector<uint8_t> &vec);
std::unordered_map<uint8_t, size_t> parallelHistogramNThreads(const std::vector<uint8_t> &vec, size_t t);
void task4(const std::vector<uint8_t> &vec, size_t t);

// Task 5 — Parallel Max Element with Lowest Index

std::pair<int, size_t> parallelMaxElementLowestIndexSingleThread(const std::vector<int> &vec);
std::pair<int, size_t> parallelMaxElementLowestIndexTwoThreads(const std::vector<int> &vec);
std::pair<int, size_t> parallelMaxElementLowestIndexNThreads(const std::vector<int> &vec, size_t t);
void task5(const std::vector<int> &vec, size_t t);

