#pragma once
#include <cstddef>
#include <algorithm>
#include <iostream>

template <typename Collection, typename Compare>
long long partition(Collection arr, long long size, Compare comp)
{
    auto i = -1LL;
    auto j = size;
    auto pivot = arr[0];

    while (true)
    {
        while (comp(arr[++i], pivot))
        {
            continue;
        }
        while (!comp(arr[--j], pivot) && arr[j] != pivot)
        {
            continue;
        }
        if (i >= j)
        {
            break;
        }
        std::swap(arr[i], arr[j]);
    }
    return j;
}

template <typename Collection, typename Compare>
void quick_sort_helper(Collection arr, long long size, Compare comp)
{
    if (size < 2)
    {
        return;
    }
    auto pivot_idx = partition(arr, size, comp);
    quick_sort_helper(arr, pivot_idx + 1, comp);
    quick_sort_helper(arr + pivot_idx + 1, size - pivot_idx - 1, comp);
}

template <typename Collection, typename Compare = std::less<>>
void quick_sort(Collection &arr, long long size, Compare comp = Compare())
{
    quick_sort_helper(std::begin(arr), size, comp);
}
