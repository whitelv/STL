#pragma once
#include <cstddef>
#include <algorithm>
#include <type_traits>

template <typename Collection, typename Compare = std::greater<>>
void InsertionSort(Collection &col, size_t size, Compare comp = Compare())
{
    if (size == 0)
    {
        return;
    }
    std::remove_reference_t<decltype(col[0])> current_el;
    for (size_t i = 1; i < size; i++)
    {
        current_el = col[i];
        size_t j = i;

        while (j >= 1 && comp(col[j - 1],current_el))
        {
            col[j] = col[j - 1];
            j--;
        }
        col[j] = current_el;
    }
}

