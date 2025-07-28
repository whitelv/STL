#pragma once
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <functional>

template <typename Collection, typename Compare = std::greater<>>
void BubbleSort(Collection &con, size_t size, Compare comp = Compare())
{
    if (size == 0)
    {
        return;
    }
    bool is_sorted;

    for (size_t i = 0; i < size; i++)
    {
        bool is_sorted = true;
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (comp(con[j], con[j + 1]))
            {
                std::swap(con[j], con[j + 1]);
                is_sorted = false;
            }
        }
        
        if (is_sorted)
        {
            break;
        }
    }
}
