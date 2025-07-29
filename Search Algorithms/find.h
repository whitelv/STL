#pragma once
#include <cstddef>
#include <iostream>
#include <cmath>
template <typename RandomAccessIterator>
void display(RandomAccessIterator begin, RandomAccessIterator end)
{
    while (begin != end)
    {
        std::cout << *begin++ << " ";
    }
    std::cout << std::endl;
}

// #  Check if an element X exists in a sorted container.
template <typename RandomAccessIterator, typename T, typename Compare = std::greater<T>>
bool binarySearch(RandomAccessIterator begin, RandomAccessIterator end, const T &target, Compare comp = Compare{})
{
    if (begin == end)
    {
        return 0;
    }
    auto low = begin;
    auto high = end - 1;

    while (low <= high)
    {
        auto mid = low + (high - low) / 2;
        if (*mid == target)
        {
            return 1;
        }
        if (comp(*mid, target))
        {
            high = --mid;
        }
        else
        {
            low = ++mid;
        }
    }
    return 0;
}

template <typename InputIterator, typename T>
bool linearSearch(InputIterator begin, InputIterator end, const T &target)
{
    if (begin == end)
    {
        return 0;
    }
    while (begin != end)
    {
        if (*begin++ == target)
        {
            return 1;
        }
    }
    return 0;
}

// # Find the first element greater than or equal to X.
template <typename InputIterator, typename T>
InputIterator greaterEqualThan(InputIterator begin, InputIterator end, const T &target)
{
    if (begin == end)
    {
        return end;
    }
    while (begin != end)
    {
        if (*begin >= target)
        {
            return begin;
        }
        begin++;
    }
    return end;
}

template <typename RandomAccessIterator, typename T, typename Compare = std::less<T>>
RandomAccessIterator greaterEqualThanBinary(RandomAccessIterator begin, RandomAccessIterator end, const T &target, Compare comp = Compare{})
{
    if (begin == end)
    {
        return end;
    }
    auto low = begin;
    auto high = end - 1;
    RandomAccessIterator mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        display(low, high + 1);
        if (comp(*mid, target))
        {
            low = mid + 1;
        }
        else if (mid == begin || comp(*(mid - 1), target))
        {
            break;
        }
        else
        {
            high = mid - 1;
        }
    }
    return low > high ? low : mid;
}

// # Find the first element strictly greater than X.
template <typename InputIterator, typename T>
InputIterator greaterThan(InputIterator begin, InputIterator end, const T &target)
{
    if (begin == end)
    {
        return end;
    }
    while (begin != end)
    {
        if (*begin > target)
        {
            return begin;
        }
        begin++;
    }
    return end;
}

template <typename RandomAccessIterator, typename T, typename Compare = std::less_equal<>>
RandomAccessIterator greaterThanBinary(RandomAccessIterator begin, RandomAccessIterator end, const T &target, Compare comp = Compare{})
{
    return greaterEqualThanBinary(begin, end, target, comp);
}

// # Find the position where X can be inserted to keep the container sorted.
template <typename RandomAccessIterator, typename T, typename Compare = std::less<T>>
size_t findInsertPosition(RandomAccessIterator begin, RandomAccessIterator end, const T &target, Compare comp = Compare{})
{
    if (begin == end)
    {
        return 0;
    }
    auto low = begin;
    auto high = end - 1;
    RandomAccessIterator mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (comp(*mid, target))
        {
            low = mid + 1;
        }
        else if (mid == begin || comp(*(mid - 1), target))
        {
            break;
        }
        else
        {
            high = mid - 1;
        }
    }
    return low > high ? low - begin : mid - begin;
}

// # Count how many times X appears in a sorted container.

template <typename RandomAccessIterator, typename T>
RandomAccessIterator firstEqual(RandomAccessIterator begin, RandomAccessIterator end, const T &target)
{
    if (begin == end)
    {
        return end;
    }
    auto low = begin;
    auto high = end - 1;
    RandomAccessIterator mid;
    bool is_found = false;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (*mid < target)
        {
            low = mid + 1;
        }
        else if (*mid > target)
        {
            high = mid - 1;
        }
        else if (mid == begin)
        {
            if (*mid == target)
            {
                is_found = true;
            }
            break;
        }
        else if (*(mid - 1) == target)
        {
            high = high - 1;
        }
        else
        {
            is_found = true;
            break;
        }
    }
    return is_found ? mid : end;
}

template <typename RandomAccessIterator, typename T>
RandomAccessIterator lastEqual(RandomAccessIterator begin, RandomAccessIterator end, const T &target)
{
    if (begin == end)
    {
        return end;
    }
    auto low = begin;
    auto high = end - 1;
    RandomAccessIterator mid;
    bool is_found = false;

    while (low <= high)
    {
        display(low, high + 1);
        mid = low + (high - low) / 2;
        if (*mid < target)
        {
            low = mid + 1;
        }
        else if (*mid > target)
        {
            high = mid - 1;
        }
        else if (mid == end - 1)
        {
            if (*mid == target)
            {
                is_found = true;
            }
            break;
        }
        else if (*(mid + 1) == target)
        {
            low = mid + 1;
        }
        else
        {
            is_found = true;
            break;
        }
    }
    return is_found ? mid : end;
}

template <typename RandomAccessIterator, typename T>
size_t TimesNBinary(RandomAccessIterator begin, RandomAccessIterator end, const T &target)
{
    if (begin == end)
    {
        return 0;
    }
    auto first = firstEqual(begin, end, target);
    auto last = lastEqual(begin, end, target);

    return last != end ? (last + 1) - first : 0;
}

// # Find the range of indices where value X appears in a sorted container.
template <typename RandomAccessIterator, typename T>
std::pair<RandomAccessIterator, RandomAccessIterator> findRange(RandomAccessIterator begin, RandomAccessIterator end, const T &target){
    if (begin == end)
    {
        return {end, end};
    }

    auto first = firstEqual(begin, end, target);
    auto last = lastEqual(begin, end, target);

    if (last != end)
    {
        return {first, last + 1};
    }
    return {end, end};
}
