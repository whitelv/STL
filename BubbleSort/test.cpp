#include <gtest/gtest.h>
#include <vector>
#include "bubble.h"

template <typename T>
bool custom_sort(const T &a, const T &b)
{
    return a < b;
}

struct customFunctor
{
    template <typename T>
    bool operator()(const T &a, const T &b)
    {
        return a < b;
    }
};

TEST(BubbleModule, testSortWithEmptyCollection)
{
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(BubbleSort(v, 0));
}

TEST(BubbleModule, testSortWithWrongSizeCollection)
{
    std::vector<int> unsorted_v{4, 3, 2, 1, 10, 9, 8, 7};
    std::vector<int> sorted_v{1, 2, 3, 4, 10, 9, 8, 7};
    BubbleSort(unsorted_v, 4);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWithDiffirentIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{4, 3, 5, 6, 7, 2, 1};
    std::vector<int> sorted_v{1, 2, 3, 4, 5, 6, 7};
    BubbleSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWithSameIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 1, 1, 1, 1, 1};
    std::vector<int> sorted_v{1, 1, 1, 1, 1, 1};
    BubbleSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWithDuplicatesIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 2, 1, 1, 2, 2};
    std::vector<int> sorted_v{1, 1, 1, 2, 2, 2};
    BubbleSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWithSortedIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> sorted_v{1, 2, 3, 4, 5, 6, 7};
    BubbleSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWithNegativeIntVectorDefaultComp)
{
    std::vector<int> unsorted_v{1, 2, 3, 0, -1, -2, -3};
    std::vector<int> sorted_v{-3, -2, -1, 0, 1, 2, 3};
    BubbleSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWithDoubleVectorDefaultComp)
{
    std::vector<double> unsorted_v{1.1, 1.3, 1.2, 1.0, 1.5, 1.6, 1.4};
    std::vector<double> sorted_v{1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    BubbleSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWithDifferentIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {4, 3, 5, 6, 7, 2, 1};
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    BubbleSort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    }
}

TEST(BubbleModule, testSortWithSameIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 1, 1, 1, 1, 1};
    int sorted_arr[] = {1, 1, 1, 1, 1, 1};
    BubbleSort(unsorted_arr, 6);
    for (size_t i = 0; i < 6; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(BubbleModule, testSortWithDuplicatesIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 2, 1, 1, 2, 2};
    int sorted_arr[] = {1, 1, 1, 2, 2, 2};
    BubbleSort(unsorted_arr, 6);
    for (size_t i = 0; i < 6; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(BubbleModule, testSortWithSortedRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7};
    BubbleSort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(BubbleModule, testSortWithNegativeIntRawArrayDefaultComp)
{
    int unsorted_arr[] = {1, 2, 3, 0, -1, -2, -3};
    int sorted_arr[] = {-3, -2, -1, 0, 1, 2, 3};
    BubbleSort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}

TEST(BubbleModule, testSortWithDoubleRawArrayDefaultComp)
{
    double unsorted_arr[] = {1.1, 1.3, 1.2, 1.0, 1.5, 1.6, 1.4};
    double sorted_arr[] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    BubbleSort(unsorted_arr, 7);
    for (size_t i = 0; i < 7; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    };
}


TEST(BubbleModule, testSortWithDiffirentCharCstringDefaultComp)
{
    char unsorted_str[] = "dbcafe";
    char sorted_str[] = "abcdef";
    BubbleSort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(BubbleModule, testSortWithSameCharCstringDefaultComp)
{
    char unsorted_str[] = "aaaaaa";
    char sorted_str[] = "aaaaaa";
    BubbleSort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(BubbleModule, testSortWithDuplicateCharCstringDefaultComp)
{
    char unsorted_str[] = "ababab";
    char sorted_str[] = "aaabbb";
    BubbleSort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(BubbleModule, testSortWithSortedCharCstringDefaultComp)
{
    char unsorted_str[] = "abcdef";
    char sorted_str[] = "abcdef";
    BubbleSort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(BubbleModule, testSortWithSpaceCharCstringDefaultComp)
{
    char unsorted_str[] = "      ";
    char sorted_str[] = "      ";
    BubbleSort(unsorted_str, 6);
    EXPECT_STREQ(unsorted_str, sorted_str);
}


TEST(BubbleModule, testSortWitIntVectorCustomFunction)
{
    std::vector<int> unsorted_v{3, 2, 4, 1};
    std::vector<int> sorted_v{4, 3, 2, 1};
    BubbleSort(unsorted_v, unsorted_v.size(), custom_sort<int>);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWitIntVectorCustomFunctor)
{
    std::vector<int> unsorted_v{3, 2, 4, 1};
    std::vector<int> sorted_v{4, 3, 2, 1};
    BubbleSort(unsorted_v, unsorted_v.size(), customFunctor());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWitIntVectorCustomLambda)
{
    std::vector<int> unsorted_v{3, 2, 4, 1};
    std::vector<int> sorted_v{4, 3, 2, 1};
    BubbleSort(unsorted_v, unsorted_v.size(), [](const auto &a, const auto &b)
               { return a < b; });
    EXPECT_EQ(unsorted_v, sorted_v);
}
