#include <gtest/gtest.h>
#include "MergeSort.h"
#include <vector>


template <typename T>
bool custom_sort(const T &a, const T &b)
{
    return a > b;
}

struct customFunctor
{
    template <typename T>
    bool operator()(const T &a, const T &b)
    {
        return a > b;
    }
};


TEST(MergeSortModule, testSortWithEmptyCollection)
{
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(merge_sort(v, 0));
}

TEST(MergeSortModule, testSortWithWrongSizeCollection)
{
    std::vector<int> unsorted_v{4, 3, 2, 1, 10, 9, 8, 7};
    std::vector<int> sorted_v{1, 2, 3, 4, 10, 9, 8, 7};
    merge_sort(unsorted_v, 4);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWithDiffirentIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{4, 3, 5, 6, 7, 2, 1};
    std::vector<int> sorted_v{1, 2, 3, 4, 5, 6, 7};
    merge_sort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWithSameIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 1, 1, 1, 1, 1};
    std::vector<int> sorted_v{1, 1, 1, 1, 1, 1};
    merge_sort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWithDuplicatesIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 2, 1, 1, 2, 2};
    std::vector<int> sorted_v{1, 1, 1, 2, 2, 2};
    merge_sort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWithSortedIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> sorted_v{1, 2, 3, 4, 5, 6, 7};
    merge_sort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWithNegativeIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 2, 3, 0, -1, -2, -3};
    std::vector<int> sorted_v{-3, -2, -1, 0, 1, 2, 3};
    merge_sort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWithDoubleVectorDefaultComp)
{
    std::vector<double> unsorted_v{1.1, 1.3, 1.2, 1.0, 1.5, 1.6, 1.4};
    std::vector<double> sorted_v{1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    merge_sort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWithDifferentIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {4, 3, 5, 6, 7, 2, 1};
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    merge_sort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    }
}

TEST(MergeSortModule, testSortWithSameIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 1, 1, 1, 1, 1};
    int sorted_arr[] = {1, 1, 1, 1, 1, 1};
    merge_sort(unsorted_arr, 6);
    for (size_t i = 0; i < 6; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(MergeSortModule, testSortWithDuplicatesIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 2, 1, 1, 2, 2};
    int sorted_arr[] = {1, 1, 1, 2, 2, 2};
    merge_sort(unsorted_arr, 6);
    for (size_t i = 0; i < 6; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(MergeSortModule, testSortWithSortedRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    merge_sort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(MergeSortModule, testSortWithNegativeIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 2, 3, 0, -1, -2, -3};
    int sorted_arr[] = {-3, -2, -1, 0, 1, 2, 3};
    merge_sort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(MergeSortModule, testSortWithDoubleRawArrayDefaultComp)
{
    double unsorted_arr[] = {1.1, 1.3, 1.2, 1.0, 1.5, 1.6, 1.4};
    double sorted_arr[] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    merge_sort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}


TEST(MergeSortModule, testSortWithDiffirentCharCstringDefaultComp)
{
    char unsorted_str[] = "dbcafe";
    char sorted_str[] = "abcdef";
    merge_sort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(MergeSortModule, testSortWithSameCharCstringDefaultComp)
{
    char unsorted_str[] = "aaaaaa";
    char sorted_str[] = "aaaaaa";
    merge_sort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(MergeSortModule, testSortWithDuplicateCharCstringDefaultComp)
{
    char unsorted_str[] = "ababab";
    char sorted_str[] = "aaabbb";
    merge_sort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(MergeSortModule, testSortWithSortedCharCstringDefaultComp)
{
    char unsorted_str[] = "abcdef";
    char sorted_str[] = "abcdef";
    merge_sort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(MergeSortModule, testSortWithSpaceCharCstringDefaultComp)
{
    char unsorted_str[] = "      ";
    char sorted_str[] = "      ";
    merge_sort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}


TEST(MergeSortModule, testSortWitIntVectorCustomFunction)
{
    std::vector<int> unsorted_v{3, 2, 4, 1};
    std::vector<int> sorted_v{4, 3, 2, 1};
    merge_sort(unsorted_v, unsorted_v.size(), custom_sort<int>);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWitIntVectorCustomFunctor)
{
    std::vector<int> unsorted_v{3, 2, 4, 1};
    std::vector<int> sorted_v{4, 3, 2, 1};
    merge_sort(unsorted_v, unsorted_v.size(), customFunctor());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(MergeSortModule, testSortWitIntVectorCustomLambda)
{
    std::vector<int> unsorted_v{3, 2, 4, 1};
    std::vector<int> sorted_v{4, 3, 2, 1};
    merge_sort(unsorted_v, unsorted_v.size(), [](const auto &a, const auto &b)
               { return a > b; });
    EXPECT_EQ(unsorted_v, sorted_v);
}
