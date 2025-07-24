#include "InsertionSort.h"
#include <gtest/gtest.h>
#include <vector>


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

TEST(InsertionModule, testSortWithEmptyCollection){
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(InsertionSort(v, 0));
}

TEST(InsertionModule, testSortWithWrongSizeCollection){
    std::vector<int> unsorted_v {4,3,2,1,10,9,8,7};
    std::vector<int> sorted_v {1,2,3,4,10,9,8,7};
    InsertionSort(unsorted_v, 4);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(InsertionModule, testSortWitIntVectorDefaultComp){
    std::vector<int> unsorted_v {4,3,2,1};
    std::vector<int> sorted_v {1,2,3,4};
    InsertionSort(unsorted_v, unsorted_v.size());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(InsertionModule, testSortWitRawIntArrayDefaultComp){
    int unsorted_arr[4] = {3,4,1,2};
    int sorted_arr[4] = {1,2,3,4};
    InsertionSort(unsorted_arr, 4);
    for (size_t i = 0; i < 4; i++)
    {
        ASSERT_EQ(unsorted_arr[i], sorted_arr[i]);
    }
}

TEST(InsertionModule, testSortWithCstrngDefaultComp){
    char unsorted_str[5] = "dbca";
    char sorted_str[5] = "abcd";
    InsertionSort(unsorted_str, 4);
    EXPECT_STREQ(unsorted_str, sorted_str);
}

TEST(InsertionModule, testSortWitIntVectorCustomFunction){
    std::vector<int> unsorted_v {3,2,4,1};
    std::vector<int> sorted_v {4,3,2,1};
    InsertionSort(unsorted_v, unsorted_v.size(), custom_sort<int>);
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(InsertionModule, testSortWitIntVectorCustomFunctor){
    std::vector<int> unsorted_v {3,2,4,1};
    std::vector<int> sorted_v {4,3,2,1};
    InsertionSort(unsorted_v, unsorted_v.size(), customFunctor());
    EXPECT_EQ(unsorted_v, sorted_v);
}

TEST(InsertionModule, testSortWitIntVectorCustomLambda){
    std::vector<int> unsorted_v {3,2,4,1};
    std::vector<int> sorted_v {4,3,2,1};
    InsertionSort(unsorted_v, unsorted_v.size(), [](const auto & a, const auto & b){return a < b;});
    EXPECT_EQ(unsorted_v, sorted_v);
}
