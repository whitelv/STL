#include <gtest/gtest.h>
#include <vector>
#include <forward_list>
#include <string>
#include "find.h"


TEST(SearchModule, testBinarySearchWithEmptyVector){
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(binarySearch(v.begin(), v.end(), 1));
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementVectorTrue){
    std::vector<int> v{1};
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementVectorFalse){
    std::vector<int> v{1};
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), 0));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesVector){
    std::vector<int> v{0,1,2,3,4,5};
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 0));
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 5));
}

TEST(SearchModule, testBinarySearchWithAnyValuesVector){
    std::vector<int> v{0,1,2,3,4,5};
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 3));
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 4));
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), 7));
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), -7));
}

TEST(SearchModule, testBinarySearchWithEmptyString){
    std::string str;
    EXPECT_NO_FATAL_FAILURE(binarySearch(str.begin(), str.end(), 1));
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementStringTrue){
    std::string str = "a";
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'a'));
}

TEST(SearchModule, testBinarySearchWithOneElementStringFalse){
    std::string str = "a";
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 'b'));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesString){
    std::string str = "abcdef";
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'a'));
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'f'));
}

TEST(SearchModule, testBinarySearchWithAnyValuesString){
    std::string str = "abcdef";
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'b'));
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'c'));
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 'r'));
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 'y'));
}


TEST(SearchModule, testBinarySearchWithEmptyRawArray){
    int arr[0];
    EXPECT_FALSE(binarySearch(arr, arr + 0, 1));
}

TEST(SearchModule, testBinarySearchWithOneElementRawArrayTrue){
    int arr[1] = {1};
    EXPECT_TRUE(binarySearch(arr, arr + 1, 1));
}

TEST(SearchModule, testBinarySearchWithOneElementRawArrayFalse){
    int arr[1] = {1};
    EXPECT_FALSE(binarySearch(arr, arr + 1, 0));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesRawArray){
    int arr[6] = {0,1,2,3,4,5};
    EXPECT_TRUE(binarySearch(arr, arr + 6, 0));
    EXPECT_TRUE(binarySearch(arr, arr + 6, 5));
}

TEST(SearchModule, testBinarySearchWithAnyValuesRawArray){
    int arr[6] = {0,1,2,3,4,5};
    EXPECT_TRUE(binarySearch(arr, arr + 6, 3));
    EXPECT_TRUE(binarySearch(arr, arr + 6, 4));
    EXPECT_FALSE(binarySearch(arr, arr + 6, 7));
    EXPECT_FALSE(binarySearch(arr, arr + 6, -7));
}


TEST(SearchModule, testBinarySearchWithEmptyForwardList){
    std::forward_list<int> f;
    EXPECT_NO_FATAL_FAILURE(linearSearch(f.begin(), f.end(), 1));
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementForwardListTrue){
    std::forward_list<int> f{1};
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementForwardListFalse){
    std::forward_list<int> f{1};
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), 0));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesForwardList){
    std::forward_list<int> f{0,1,2,3,4,5};
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 0));
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 5));
}

TEST(SearchModule, testBinarySearchWithAnyValuesForwardList){
    std::forward_list<int> f{0,1,2,3,4,5};
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 3));
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 4));
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), 7));
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), -7));
}

TEST(SearchModule, testgreaterEqualThanWithEmptyVector){
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(greaterEqualThan(v.begin(), v.end(), 1));
    EXPECT_EQ(greaterEqualThan(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testgreaterEqualThanWithSortedVectorTrue){
    std::vector<int> v = {1,2,3,4,5};
    EXPECT_EQ(*greaterEqualThan(v.begin(), v.end(), 3), 3);
}

TEST(SearchModule, testgreaterEqualThanWithSortedVectorFalse){
    std::vector<int> v = {1,2,3,4,5};
    EXPECT_EQ(greaterEqualThan(v.begin(), v.end(), 6), v.end());
}

TEST(SearchModule, testgreaterEqualThanWithUnsortedSortedVector){
    std::vector<int> v = {5,2,1,6,3,7};
    EXPECT_EQ(*greaterEqualThan(v.begin(), v.end(), 6), 6);
}

TEST(SearchModule, testgreaterThanWithEmptyVector){
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(greaterThan(v.begin(), v.end(), 1));
    EXPECT_EQ(greaterThan(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testgreaterThanWithSortedVectorTrue){
    std::vector<int> v = {1,2,3,4,5};
    EXPECT_EQ(*greaterThan(v.begin(), v.end(), 3), 4);
}

TEST(SearchModule, testgreaterThanWithSortedVectorFalse){
    std::vector<int> v = {1,2,3,4,5};
    EXPECT_EQ(greaterThan(v.begin(), v.end(), 6), v.end());
}

TEST(SearchModule, testgreaterThanWithUnsortedSortedVector){
    std::vector<int> v = {5,2,1,6,3,7};
    EXPECT_EQ(*greaterThan(v.begin(), v.end(), 6), 7);
    EXPECT_EQ(*greaterThan(v.begin(), v.end(), 4), 5);
}
