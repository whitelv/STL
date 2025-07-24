#include <gtest/gtest.h>
#include <vector>
#include "bubble.h"

template <typename T>
bool custom_sort(const T & a, const T & b){
    return a < b;
}

struct customFunctor{
    template <typename T>
    bool operator()(const T & a, const T & b){
        return a < b;
    }
};

TEST(BubbleModule, testSortWithEmptyCollection){
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(BubbleSort(v, 0));
}

TEST(BubbleModule, testSortWithWrongSizeCollection){
    std::vector<int> unsorted_v {4,3,2,1,10,9,8,7};
    std::vector<int> sorted_v {1,2,3,4,10,9,8,7};
    BubbleSort(unsorted_v, 4);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWitIntVectorDefaultComp){
    std::vector<int> unsorted_v {4,3,2,1};
    std::vector<int> sorted_v {1,2,3,4};
    BubbleSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWitRawIntArrayDefaultComp){
    int unsorted_arr[4] = {3,4,1,2};
    int sorted_arr[4] = {1,2,3,4};
    BubbleSort(unsorted_arr, 4);
    for (size_t i = 0; i < 4; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    }
}

TEST(BubbleModule, testSortWithCstrngDefaultComp){
    char unsorted_str[5] = "dbca";
    char sorted_str[5] = "abcd";
    BubbleSort(unsorted_str, 4);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(BubbleModule, testSortWitIntVectorCustomFunction){
    std::vector<int> unsorted_v {3,2,4,1};
    std::vector<int> sorted_v {4,3,2,1};
    BubbleSort(unsorted_v, unsorted_v.size(), custom_sort<int>);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWitIntVectorCustomFunctor){
    std::vector<int> unsorted_v {3,2,4,1};
    std::vector<int> sorted_v {4,3,2,1};
    BubbleSort(unsorted_v, unsorted_v.size(), customFunctor());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(BubbleModule, testSortWitIntVectorCustomLambda){
    std::vector<int> unsorted_v {3,2,4,1};
    std::vector<int> sorted_v {4,3,2,1};
    BubbleSort(unsorted_v, unsorted_v.size(), [](const auto & a, const auto & b){return a < b;});
    EXPECT_EQ(unsorted_v, sorted_v);
}
