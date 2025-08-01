#pragma once
#include <cstddef>
#include <iostream>
#include <cmath>
#include <queue>
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
        return false;
    }
    auto low = begin;
    auto high = end - 1;

    while (low <= high)
    {
        auto mid = low + (high - low) / 2;
        if (*mid == target)
        {
            return true;
        }
        if (comp(*mid, target))
        {
            high = --mid;
            continue;
        }
        low = ++mid;
    }
    return false;
}

template <typename InputIterator, typename T>
bool linearSearch(InputIterator begin, InputIterator end, const T &target)
{
    if (begin == end)
    {
        return false;
    }
    while (begin != end)
    {
        if (*begin++ == target)
        {
            return true;
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
        if (comp(*mid, target))
        {
            low = mid + 1;
            continue;
        }
        if (mid == begin || comp(*(mid - 1), target))
        {
            break;
        }
        high = mid - 1;
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
            continue;
        }
        else if (mid == begin || comp(*(mid - 1), target))
        {
            break;
        }
        high = mid - 1;
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
            continue;
        }
        if (*mid > target)
        {
            high = mid - 1;
            continue;
        }
        if (mid == begin)
        {
            if (*mid == target)
            {
                is_found = true;
            }
            break;
        }
        if (*(mid - 1) == target)
        {
            high = mid - 1;
            continue;
        }

        is_found = true;
        break;
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
        mid = low + (high - low) / 2;
        if (*mid < target)
        {
            low = mid + 1;
            continue;
        }
        if (*mid > target)
        {
            high = mid - 1;
            continue;
        }
        if (mid == end - 1)
        {
            if (*mid == target)
            {
                is_found = true;
            }
            break;
        }
        if (*(mid + 1) == target)
        {
            low = mid + 1;
            continue;
        }

        is_found = true;
        break;
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
std::pair<RandomAccessIterator, RandomAccessIterator> findRange(RandomAccessIterator begin, RandomAccessIterator end, const T &target)
{
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

// # Find the first element that matches a custom predicate (e.g., even number).
template <typename InputIterator, typename Predicate>
InputIterator findFirstMatch(InputIterator begin, InputIterator end, Predicate predicate)
{
    if (begin == end)
    {
        return end;
    }
    while (begin != end)
    {
        if (predicate(*begin))
        {
            return begin;
        }
        begin++;
    }
    return begin;
}

// # Find the first element that does not match a custom predicate (e.g., odd number).
template <typename InputIterator, typename Predicate>
InputIterator findFirstNotMatch(InputIterator begin, InputIterator end, Predicate predicate)
{
    if (begin == end)
    {
        return end;
    }
    while (begin != end)
    {
        if (!predicate(*begin))
        {
            return begin;
        }
        begin++;
    }
    return begin;
}

// # Find a subsequence within another container.
template <typename InputIterator1, typename InputIterator2>
InputIterator1 findSubsequence(InputIterator1 begin_first, InputIterator1 end_first, InputIterator2 begin_second, InputIterator2 end_second)
{
    if (begin_second == end_second)
    {
        return begin_first;
    }

    if (begin_first == end_first)
    {
        return end_first;
    }
    auto current = begin_second;
    auto start = begin_first;

    while (begin_first != end_first)
    {
        if (*begin_first == *current)
        {
            if (current == begin_second)
            {
                start = begin_first;
            }

            if (++current == end_second)
            {
                return start;
            }
        }
        else
        {
            current = begin_second;
        }
        begin_first++;
    }
    return end_first;
}

// # Find N consecutive equal elements.
template <typename InputIterator>
InputIterator findNEqualConsecutive(InputIterator begin, InputIterator end, size_t n)
{
    if (begin == end || n == 0)
    {
        return end;
    }

    if (n == 1)
    {
        return begin;
    }

    auto curr = begin;
    auto currPlusOne = ++begin;
    auto start = curr;
    size_t count = 1;

    while (currPlusOne != end)
    {

        if (*currPlusOne == *curr)
        {
            if (count == 1)
            {
                start = curr;
            }

            if (++count == n)
            {
                return start;
            }
        }
        else
        {
            count = 1;
        }
        curr++;
        currPlusOne++;
    }

    return end;
}

// # Find the first pair of adjacent equal elements.
template <typename InputIterator>
InputIterator findAdjacentEqual(InputIterator begin, InputIterator end)
{
    if (begin == end)
    {
        return end;
    }
    auto curr = begin;
    auto currPlusOne = ++begin;

    while (currPlusOne != end)
    {
        if (*currPlusOne == *curr)
        {
            return curr;
        }
        currPlusOne++;
        curr++;
    }
    return end;
}

// # Find the first position where two containers differ.
template <typename RandomAccessIterator1, typename RandomAccessIterator2>
std::pair<RandomAccessIterator1, RandomAccessIterator2> findFirstMismatchRandomAccess(RandomAccessIterator1 begin_first, RandomAccessIterator1 end_first, RandomAccessIterator2 begin_second, RandomAccessIterator2 end_second)
{
    size_t size1 = std::distance(begin_first, end_first);
    size_t size2 = std::distance(begin_second, end_second);

    if (size1 == 0 && size2 == 0)
    {
        return {end_first, end_second};
    }

    if (size1 > size2)
    {
        return {begin_first + size2, end_second};
    }
    if (size2 > size1)
    {
        return {end_first, begin_second + size1};
    }

    while (begin_first != end_first)
    {
        if (*begin_first != *begin_second)
        {
            return {begin_first, begin_second};
        }
        begin_first++;
        begin_second++;
    }
    return {end_first, end_second};
}

template <typename InputIterator1, typename InputIterator2>
std::pair<InputIterator1, InputIterator2> findFirstMismatchInput(InputIterator1 begin_first, InputIterator1 end_first, InputIterator2 begin_second, InputIterator2 end_second)
{
    while (begin_first != end_first && begin_second != end_second)
    {
        if (*begin_first != *begin_second)
        {
            return {begin_first, begin_second};
        }
        begin_first++;
        begin_second++;
    }
    return {begin_first, begin_second};
}

// # Check if the container is sorted.
template <typename InputIterator, typename Compare = std::less<>>
bool isSorted(InputIterator begin, InputIterator end, Compare comp = Compare{})
{
    if (begin == end)
    {
        return true;
    }
    auto curr = begin;
    auto currPlusOne = ++begin;

    while (currPlusOne != end)
    {
        if (comp(*currPlusOne, *curr))
        {
            return false;
        }
        curr++;
        currPlusOne++;
    }
    return true;
}

// # Find the first element where sorting order breaks.
template <typename InputIterator, typename Compare = std::less<>>
InputIterator findFirstUnsorted(InputIterator begin, InputIterator end, Compare comp = Compare{})
{
    if (begin == end)
    {
        return end;
    }
    auto curr = begin;
    auto currPlusOne = ++begin;

    while (currPlusOne != end)
    {
        if (comp(*currPlusOne, *curr))
        {
            return currPlusOne;
        }
        curr++;
        currPlusOne++;
    }

    return end;
}

// # Partition even and odd numbers, then find the first odd number.
template <typename RandomAccessIterator, typename Predicate>
void Partition(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate)
{
    size_t size = std::distance(begin, end);
    if (size < 2)
    {
        return;
    }

    size_t middle = std::ceil(size / 2.0) - 1;
    auto newBeginEnd = begin + middle;

    Partition(begin, newBeginEnd + 1, predicate);
    Partition(newBeginEnd + 1, end, predicate);

    std::vector<std::remove_reference_t<decltype(*begin)>> vec;

    auto start1 = begin;
    auto start2 = newBeginEnd + 1;

    while (true)
    {
        if (start1 != newBeginEnd + 1 && predicate(*start1))
        {
            vec.push_back(*start1);
            start1++;
            continue;
        }
        if (start2 != end && predicate(*start2))
        {
            vec.push_back(*start2);
            start2++;
            continue;
        }
        break;
    }
    while (start1 != newBeginEnd + 1)
    {
        vec.push_back(*start1++);
    }
    while (start2 != end)
    {
        vec.push_back(*start2++);
    }

    size_t i = 0;
    while (begin != end)
    {
        *begin = vec[i];
        i++;
        begin++;
    }
}

template <typename RandomAccessIterator>
RandomAccessIterator partitionAndFindFirstOdd(RandomAccessIterator begin, RandomAccessIterator end)
{
    if (begin == end)
    {
        return end;
    }

    Partition(begin, end, [](const auto &a)
              { return a % 2 != 0; });
    return *begin % 2 != 0 ? begin : end;
}

// # Check if a range contains a specific subrange.
template <typename InputIterator1, typename InputIterator2>
bool containsSubrange(InputIterator1 begin_first, InputIterator1 end_first, InputIterator2 begin_second, InputIterator2 end_second)
{
    if (begin_second == end_second)
    {
        return true;
    }

    if (begin_first == end_first)
    {
        return false;
    }
    auto current = begin_second;
    while (begin_first != end_first)
    {
        if (*begin_first == *current)
        {
            current++;
            if (current == end_second)
            {
                return true;
            }
        }
        else
        {
            current = begin_second;
        }
        begin_first++;
    }
    return false;
}

// # Find the first element greater than the mean of all elements.

template <typename InputIterator>
InputIterator findFirstAboveMean(InputIterator begin, InputIterator end)
{
    if (begin == end)
    {
        return end;
    }
    double sum{};
    size_t count = 0;

    auto current = begin;
    while (current != end)
    {
        sum += *current++;
        count++;
    }

    double mean = sum / count;

    while (begin != end)
    {
        if (*begin > mean)
        {
            return begin;
        }
        begin++;
    }
    return end;
}

// # Find the first element smaller than its previous element.
template <typename InputIterator>
InputIterator findFirstDrop(InputIterator begin, InputIterator end)
{
    if (begin == end)
    {
        return end;
    }
    auto curr = begin;
    auto currPlusOne = ++begin;

    while (currPlusOne != end)
    {
        if (*currPlusOne < *curr)
        {
            return currPlusOne;
        }
        currPlusOne++;
        curr++;
    }

    return end;
}

// # Find the longest run of consecutive equal elements.
template <typename InputIterator>
InputIterator findLongestStreak(InputIterator begin, InputIterator end)
{

    if (begin == end)
    {
        return end;
    }
    auto curr = begin;
    auto currPlusOne = ++begin;

    auto start = curr;
    auto longest_start = start;

    size_t current_score = 1;
    size_t longest_score = 1;

    while (currPlusOne != end)
    {
        if (*currPlusOne == *curr)
        {
            if (current_score == 1)
            {
                start = curr;
            }
            current_score++;
        }
        else
        {
            current_score = 1;
        }

        if (current_score > longest_score)
        {
            longest_score = current_score;
            longest_start = start;
        }

        curr++;
        currPlusOne++;
    }

    return longest_start;
}