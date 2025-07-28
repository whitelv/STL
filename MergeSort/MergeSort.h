#pragma once
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <queue>

void display(int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "[ " << arr[i] << " ] " << std::flush;
    }
    std::cout << std::endl;
}

template <typename Begin, typename Compare>
void merge(Begin arr, Begin left_arr, Begin right_arr, size_t size, size_t left_size, size_t right_size, Compare comp)
{
    size_t i = 0;
    size_t j = 0;

    std::vector<std::remove_reference_t<decltype(*left_arr)>> temp;

    while (true)
    {
        if (comp(left_arr[i], right_arr[j]))
        {
            temp.push_back(left_arr[i]);
            i++;
        }
        else
        {
            temp.push_back(right_arr[j]);
            j++;
        }

        if (i >= left_size)
        {
            for (; j < right_size; j++)
            {
                temp.push_back(right_arr[j]);
            }
            break;
        }

        if (j >= right_size)
        {
            for (; i < left_size; i++)
            {
                temp.push_back(left_arr[i]);
            }
            break;
        }
    }
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = temp[i];
    }
}

template <typename Begin, typename Compare>
void merge_sort_helper(Begin arr, size_t size, Compare comp)
{
    if (size < 2)
    {
        return;
    }
    size_t middle = std::ceil(size / 2.0) - 1;
    size_t left_size = middle + 1;
    size_t right_size = size - middle - 1;
    auto left_arr = arr;
    auto right_arr = arr + middle + 1;

    merge_sort_helper(left_arr, left_size, comp);
    merge_sort_helper(right_arr, right_size, comp);
    merge(arr, left_arr, right_arr, size, left_size, right_size, comp);
}

template <typename Collection, typename Compare = std::less<>>
void merge_sort(Collection &coll, size_t size, Compare copm = Compare())
{
    merge_sort_helper(std::begin(coll), size, copm);
}