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

    task1(vec, 4);
}