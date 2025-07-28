#pragma once
#include <cstddef>
#include <algorithm>
#include <iostream>

template <typename Collection, typename Compare>
long long partition(Collection arr, size_t size, Compare comp)
{
    auto i = -1LL;
    auto j = 0LL;
    auto &pivot = arr[size - 1];

    while (j < size - 1)
    {
        if (comp(arr[j], pivot))
        {
            std::swap(arr[++i], arr[j]);
        }
        j++;
    }
    std::swap(arr[++i], pivot);
    return i;
}

template <typename Collection, typename Compare = std::less<>>
void quick_sort_helper(Collection arr, size_t size, Compare comp)
{
    if (size == 0)
    {
        return;
    }
    size_t pivot_index = partition(arr, size, comp);

    if (size > 2)
    {
        quick_sort_helper(arr, pivot_index, comp);
        quick_sort_helper(arr + pivot_index + 1, size - pivot_index - 1, comp);
    }
}

template <typename Collection, typename Compare = std::less<>>
void quick_sort(Collection & arr, size_t size, Compare comp = Compare()){
    quick_sort_helper(std::begin(arr), size, comp);
}


