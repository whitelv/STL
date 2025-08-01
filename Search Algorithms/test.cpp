#include <gtest/gtest.h>
#include <vector>
#include <forward_list>
#include <string>
#include "find.h"

template <typename T>
bool predicateFunction(const T &a)
{
    return a % 2 == 0;
}

// # binarySearch
TEST(SearchModule, testBinarySearchWithEmptyVector)
{
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(binarySearch(v.begin(), v.end(), 1));
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementVectorTrue)
{
    std::vector<int> v{1};
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementVectorFalse)
{
    std::vector<int> v{1};
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), 0));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesVector)
{
    std::vector<int> v{0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 0));
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 5));
}

TEST(SearchModule, testBinarySearchWithAnyValuesVector)
{
    std::vector<int> v{0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 3));
    EXPECT_TRUE(binarySearch(v.begin(), v.end(), 4));
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), 7));
    EXPECT_FALSE(binarySearch(v.begin(), v.end(), -7));
}

TEST(SearchModule, testBinarySearchWithEmptyString)
{
    std::string str;
    EXPECT_NO_FATAL_FAILURE(binarySearch(str.begin(), str.end(), 1));
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementStringTrue)
{
    std::string str = "a";
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'a'));
}

TEST(SearchModule, testBinarySearchWithOneElementStringFalse)
{
    std::string str = "a";
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 'b'));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesString)
{
    std::string str = "abcdef";
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'a'));
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'f'));
}

TEST(SearchModule, testBinarySearchWithAnyValuesString)
{
    std::string str = "abcdef";
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'b'));
    EXPECT_TRUE(binarySearch(str.begin(), str.end(), 'c'));
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 'r'));
    EXPECT_FALSE(binarySearch(str.begin(), str.end(), 'y'));
}

TEST(SearchModule, testBinarySearchWithEmptyRawArray)
{
    int arr[0];
    EXPECT_FALSE(binarySearch(arr, arr + 0, 1));
}

TEST(SearchModule, testBinarySearchWithOneElementRawArrayTrue)
{
    int arr[1] = {1};
    EXPECT_TRUE(binarySearch(arr, arr + 1, 1));
}

TEST(SearchModule, testBinarySearchWithOneElementRawArrayFalse)
{
    int arr[1] = {1};
    EXPECT_FALSE(binarySearch(arr, arr + 1, 0));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesRawArray)
{
    int arr[6] = {0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(binarySearch(arr, arr + 6, 0));
    EXPECT_TRUE(binarySearch(arr, arr + 6, 5));
}

TEST(SearchModule, testBinarySearchWithAnyValuesRawArray)
{
    int arr[6] = {0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(binarySearch(arr, arr + 6, 3));
    EXPECT_TRUE(binarySearch(arr, arr + 6, 4));
    EXPECT_FALSE(binarySearch(arr, arr + 6, 7));
    EXPECT_FALSE(binarySearch(arr, arr + 6, -7));
}

// # linearSearch
TEST(SearchModule, testBinarySearchWithEmptyForwardList)
{
    std::forward_list<int> f;
    EXPECT_NO_FATAL_FAILURE(linearSearch(f.begin(), f.end(), 1));
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementForwardListTrue)
{
    std::forward_list<int> f{1};
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 1));
}

TEST(SearchModule, testBinarySearchWithOneElementForwardListFalse)
{
    std::forward_list<int> f{1};
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), 0));
}

TEST(SearchModule, testBinarySearchWithEdgeValuesForwardList)
{
    std::forward_list<int> f{0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 0));
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 5));
}

TEST(SearchModule, testBinarySearchWithAnyValuesForwardList)
{
    std::forward_list<int> f{0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 3));
    EXPECT_TRUE(linearSearch(f.begin(), f.end(), 4));
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), 7));
    EXPECT_FALSE(linearSearch(f.begin(), f.end(), -7));
}

// # greaterEqual
TEST(SearchModule, testgreaterEqualThanWithEmptyVector)
{
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(greaterEqualThan(v.begin(), v.end(), 1));
    EXPECT_EQ(greaterEqualThan(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testgreaterEqualThanWithSortedVectorTrue)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(*greaterEqualThan(v.begin(), v.end(), 3), 3);
}

TEST(SearchModule, testgreaterEqualThanWithSortedVectorFalse)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(greaterEqualThan(v.begin(), v.end(), 6), v.end());
}

TEST(SearchModule, testgreaterEqualThanWithUnsortedSortedVector)
{
    std::vector<int> v = {5, 2, 1, 6, 3, 7};
    EXPECT_EQ(*greaterEqualThan(v.begin(), v.end(), 6), 6);
}

TEST(SearchModule, testgreaterEqualThanWithUnsortedSortedForwardList)
{
    std::forward_list<int> f = {5, 2, 1, 6, 3, 7};
    EXPECT_EQ(*greaterEqualThan(f.begin(), f.end(), 6), 6);
}

// # greaterThan
TEST(SearchModule, testgreaterThanWithEmptyVector)
{
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(greaterThan(v.begin(), v.end(), 1));
    EXPECT_EQ(greaterThan(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testgreaterThanWithSortedVectorTrue)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(*greaterThan(v.begin(), v.end(), 3), 4);
}

TEST(SearchModule, testgreaterThanWithSortedVectorFalse)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(greaterThan(v.begin(), v.end(), 6), v.end());
}

TEST(SearchModule, testgreaterThanWithUnsortedSortedVector)
{
    std::vector<int> v = {5, 2, 1, 6, 3, 7};
    EXPECT_EQ(*greaterThan(v.begin(), v.end(), 6), 7);
    EXPECT_EQ(*greaterThan(v.begin(), v.end(), 4), 5);
}

TEST(SearchModule, testgreaterThanWithUnsortedSortedForwardList)
{
    std::forward_list<int> f = {5, 2, 1, 6, 3, 7};
    EXPECT_EQ(*greaterThan(f.begin(), f.end(), 6), 7);
    EXPECT_EQ(*greaterThan(f.begin(), f.end(), 4), 5);
}

// # greaterEqualThanBinary
TEST(SearchModule, testgreaterEqualThanBinaryWithEmptyVector)
{
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(greaterEqualThanBinary(v.begin(), v.end(), 1));
    EXPECT_EQ(greaterEqualThanBinary(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testgreaterEqualThanBinaryWithSortedVectorTrue)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 7};
    EXPECT_EQ(*greaterEqualThanBinary(v.begin(), v.end(), 3), 3);
    EXPECT_EQ(*greaterEqualThanBinary(v.begin(), v.end(), 6), 7);
}

TEST(SearchModule, testgreaterEqualThanBinaryWithSortedVectorFalse)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(greaterEqualThanBinary(v.begin(), v.end(), 6), v.end());
}

// # greaterThanBinary
TEST(SearchModule, testgreaterThanBinaryWithEmptyVector)
{
    std::vector<int> v;
    EXPECT_NO_FATAL_FAILURE(greaterThanBinary(v.begin(), v.end(), 1));
    EXPECT_EQ(greaterThanBinary(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testgreaterThanBinaryWithSortedVectorTrue)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 7};
    EXPECT_EQ(*greaterThanBinary(v.begin(), v.end(), 3), 4);
    EXPECT_EQ(*greaterThanBinary(v.begin(), v.end(), 6), 7);
}

TEST(SearchModule, testgreaterThanBinaryWithSortedVectorFalse)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(greaterThanBinary(v.begin(), v.end(), 6), v.end());
}

// # findInsertPosition
TEST(SearchModule, testFindInsertPositionWithEmptyVector)
{
    std::vector<int> v = {};
    EXPECT_EQ(findInsertPosition(v.begin(), v.end(), 10), 0);
}

TEST(SearchModule, testFindInsertPositionWithSortedVectorEndPos)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(findInsertPosition(v.begin(), v.end(), 8), 7);
}

TEST(SearchModule, testFindInsertPositionWithSortedVectorStartPos)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(findInsertPosition(v.begin(), v.end(), 0), 0);
}

TEST(SearchModule, testFindInsertPositionWithSortedVectorMiddlePos)
{
    std::vector<int> v = {1, 2, 3, 5, 6, 7};
    EXPECT_EQ(findInsertPosition(v.begin(), v.end(), 4), 3);
}

TEST(SearchModule, testFindInsertPositionWithSortedVectorDuplicates)
{
    std::vector<int> v = {1, 2, 2, 2, 2};
    EXPECT_EQ(findInsertPosition(v.begin(), v.end(), 2), 1);
}

// # firstEqual
TEST(SearchModule, testfirstEqualWithEmptyVector)
{
    std::vector<int> v = {};
    EXPECT_EQ(firstEqual(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testfirstEqualWithSortedVectorNoDuplicates)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(firstEqual(v.begin(), v.end(), 2), ++v.begin());
}

TEST(SearchModule, testfirstEqualWithSortedVectorDuplicates)
{
    std::vector<int> v = {1, 2, 3, 3, 4, 5};
    EXPECT_EQ(firstEqual(v.begin(), v.end(), 3), ++(++v.begin()));
}

TEST(SearchModule, testfirstEqualWithSortedVectorNoTargetValue)
{
    std::vector<int> v = {1, 2, 3, 3, 4, 5};
    EXPECT_EQ(firstEqual(v.begin(), v.end(), 6), v.end());
}

// # lastEqual
TEST(SearchModule, testlastEqualWithEmptyVector)
{
    std::vector<int> v = {};
    EXPECT_EQ(lastEqual(v.begin(), v.end(), 1), v.end());
}

TEST(SearchModule, testlastEqualWithSortedVectorNoDuplicates)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(lastEqual(v.begin(), v.end(), 2), ++v.begin());
}

TEST(SearchModule, testlastEqualWithSortedVectorDuplicates)
{
    std::vector<int> v = {1, 2, 3, 3, 4, 5};
    EXPECT_EQ(lastEqual(v.begin(), v.end(), 3), ++(++(++v.begin())));
}

TEST(SearchModule, testlastEqualWithSortedVectorNoTargetValue)
{
    std::vector<int> v = {1, 2, 3, 3, 4, 5};
    EXPECT_EQ(lastEqual(v.begin(), v.end(), 6), v.end());
}

// # TimesNBinary
TEST(SearchModule, testTimesNBinaryWithEmptyVector)
{
    std::vector<int> v = {};
    EXPECT_EQ(TimesNBinary(v.begin(), v.end(), 1), 0);
}

TEST(SearchModule, testTimesNBinaryWithSortedVectorNoDuplicates)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(TimesNBinary(v.begin(), v.end(), 2), 1);
}

TEST(SearchModule, testTimesNBinaryWithSortedVectorMiddleDuplicates)
{
    std::vector<int> v = {1, 2, 3, 3, 3, 4, 5};
    EXPECT_EQ(TimesNBinary(v.begin(), v.end(), 3), 3);
}

TEST(SearchModule, testTimesNBinaryWithSortedVectorStartDuplicates)
{
    std::vector<int> v = {1, 1, 1, 1, 2, 3, 3, 3, 4, 5};
    EXPECT_EQ(TimesNBinary(v.begin(), v.end(), 1), 4);
}

TEST(SearchModule, testTimesNBinaryWithSortedVectorEndDuplicates)
{
    std::vector<int> v = {1, 2, 3, 3, 3, 3};
    EXPECT_EQ(TimesNBinary(v.begin(), v.end(), 3), 4);
}

TEST(SearchModule, testTimesNBinaryWithSortedVectorOnlyTargetDuplicates)
{
    std::vector<int> v = {3, 3, 3, 3};
    EXPECT_EQ(TimesNBinary(v.begin(), v.end(), 3), 4);
}

// # findRange
TEST(SearchModule, testfindRangeWithEmptyVector)
{
    std::vector<int> v = {};
    auto r = findRange(v.begin(), v.end(), 1);
    EXPECT_EQ(r.first, v.end());
    EXPECT_EQ(r.first, firstEqual(v.begin(), v.end(), 1));
    EXPECT_EQ(r.second, v.end());
    EXPECT_EQ(r.second, lastEqual(v.begin(), v.end(), 1));
}

TEST(SearchModule, testfindRangeWithSortedVectorNoDuplicates)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto r = findRange(v.begin(), v.end(), 2);
    EXPECT_EQ(r.first, ++v.begin());
    EXPECT_EQ(r.first, firstEqual(v.begin(), v.end(), 2));
    EXPECT_EQ(r.second, ++(++v.begin()));
    EXPECT_EQ(r.second, lastEqual(v.begin(), v.end(), 2) + 1);
}

TEST(SearchModule, testfindRangeWithSortedVectorMiddleDuplicates)
{
    std::vector<int> v = {1, 2, 3, 3, 3, 4, 5};
    auto r = findRange(v.begin(), v.end(), 3);
    EXPECT_EQ(r.first, ++(++v.begin()));
    EXPECT_EQ(r.first, firstEqual(v.begin(), v.end(), 3));
    EXPECT_EQ(r.second, (--(--v.end())));
    EXPECT_EQ(r.second, lastEqual(v.begin(), v.end(), 3) + 1);
}

TEST(SearchModule, testfindRangeWithSortedVectorStartDuplicates)
{
    std::vector<int> v = {1, 1, 1, 1, 2, 3, 3, 3, 4, 5};
    auto r = findRange(v.begin(), v.end(), 1);
    EXPECT_EQ(r.first, (v.begin()));
    EXPECT_EQ(r.first, firstEqual(v.begin(), v.end(), 1));
    EXPECT_EQ(r.second, ++(++(++(++v.begin()))));
    EXPECT_EQ(r.second, lastEqual(v.begin(), v.end(), 1) + 1);
}

TEST(SearchModule, testfindRangeWithSortedVectorEndDuplicates)
{
    std::vector<int> v = {1, 2, 3, 3, 3, 3};
    auto r = findRange(v.begin(), v.end(), 3);
    EXPECT_EQ(r.first, ++(++v.begin()));
    EXPECT_EQ(r.first, firstEqual(v.begin(), v.end(), 3));
    EXPECT_EQ(r.second, v.end());
    EXPECT_EQ(r.second, lastEqual(v.begin(), v.end(), 3) + 1);
}

TEST(SearchModule, testfindRangeWithSortedVectorOnlyTargetDuplicates)
{
    std::vector<int> v = {3, 3, 3, 3};
    auto r = findRange(v.begin(), v.end(), 3);
    EXPECT_EQ(r.first, v.begin());
    EXPECT_EQ(r.first, firstEqual(v.begin(), v.end(), 3));
    EXPECT_EQ(r.second, v.end());
    EXPECT_EQ(r.second, lastEqual(v.begin(), v.end(), 3) + 1);
}

// # findFirstMatch
TEST(SearchModule, testfindFirstMatchWithEmptyForwardList)
{
    std::forward_list<int> f = {};
    EXPECT_EQ(findFirstMatch(f.begin(), f.end(), predicateFunction<int>), f.end());
}

TEST(SearchModule, testfindFirstMatchWithUnsortedForwardListMatch)
{
    std::forward_list<int> f = {7, 5, 3, 1, 2, 4, 6};
    EXPECT_EQ(*findFirstMatch(f.begin(), f.end(), predicateFunction<int>), 2);
}

TEST(SearchModule, testfindFirstMatchWithSortedForwardListMatch)
{
    std::forward_list<int> f = {1, 4, 6, 7, 8};
    EXPECT_EQ(*findFirstMatch(f.begin(), f.end(), predicateFunction<int>), 4);
}

TEST(SearchModule, testfindFirstMatchWithSortedForwardListNoMatch)
{
    std::forward_list<int> f = {1, 3, 5};
    EXPECT_EQ(findFirstMatch(f.begin(), f.end(), predicateFunction<int>), f.end());
}

// # findFirstNotMatch

TEST(SearchModule, testfindFirstNotMatchWithEmptyForwardList)
{
    std::forward_list<int> f = {};
    EXPECT_EQ(findFirstNotMatch(f.begin(), f.end(), predicateFunction<int>), f.end());
}

TEST(SearchModule, testfindFirstNotMatchWithUnsortedForwardListMatch)
{
    std::forward_list<int> f = {7, 5, 3, 1, 2, 4, 6};
    EXPECT_EQ(*findFirstNotMatch(f.begin(), f.end(), predicateFunction<int>), 7);
}

TEST(SearchModule, testfindFirstNotMatchWithSortedForwardListMatch)
{
    std::forward_list<int> f = {1, 4, 6, 7, 8};
    EXPECT_EQ(*findFirstNotMatch(f.begin(), f.end(), predicateFunction<int>), 1);
}

TEST(SearchModule, testfindFirstNotMatchWithSortedForwardListNoMatch)
{
    std::forward_list<int> f = {2, 4, 6};
    EXPECT_EQ(findFirstNotMatch(f.begin(), f.end(), predicateFunction<int>), f.end());
}

// # findSubsequence

TEST(SearchModule, testfindSubsequenceWithEmptySubsequence)
{
    std::forward_list<int> f1 = {1, 4, 6, 7, 8};
    std::forward_list<int> f2 = {};
    EXPECT_EQ(findSubsequence(f1.begin(), f1.end(), f2.begin(), f2.end()), f1.begin());
}

TEST(SearchModule, testfindSubsequenceWithEmptySequence)
{
    std::forward_list<int> f1 = {};
    std::forward_list<int> f2 = {1};
    EXPECT_EQ(findSubsequence(f1.begin(), f1.end(), f2.begin(), f2.end()), f1.end());
}

TEST(SearchModule, testfindSubsequenceWithSameSequence)
{
    std::forward_list<int> f1 = {1, 2, 3};
    EXPECT_EQ(findSubsequence(f1.begin(), f1.end(), f1.begin(), f1.end()), f1.begin());
}

TEST(SearchModule, testfindSubsequenceWithDiffSubsequenceTrue)
{
    std::forward_list<int> f1 = {1, 2, 3};
    std::forward_list<int> f2 = {2, 3};
    EXPECT_EQ(findSubsequence(f1.begin(), f1.end(), f2.begin(), f2.end()), ++f1.begin());
}

TEST(SearchModule, testfindSubsequenceWithDiffSubsequenceFalse)
{
    std::forward_list<int> f1 = {1, 2, 3};
    std::forward_list<int> f2 = {4, 5};
    EXPECT_EQ(findSubsequence(f1.begin(), f1.end(), f2.begin(), f2.end()), f1.end());
}

// # findNEqualConsecutive
TEST(SearchModule, testfindNEqualConsecutiveWithEmptyForwardList)
{
    std::forward_list<int> f = {};
    EXPECT_EQ(findNEqualConsecutive(f.begin(), f.end(), 10), f.end());
}

TEST(SearchModule, testfindNEqualConsecutiveNonEmptyForwardListTrue)
{
    std::forward_list<int> f = {1, 2, 2, 2, 2, 3};
    EXPECT_EQ(findNEqualConsecutive(f.begin(), f.end(), 4), ++f.begin());
}

TEST(SearchModule, testfindNEqualConsecutiveNonEmptyForwardListFalse)
{
    std::forward_list<int> f = {1, 2, 2, 2, 2, 3};
    EXPECT_EQ(findNEqualConsecutive(f.begin(), f.end(), 5), f.end());
}

TEST(SearchModule, testfindNEqualConsecutiveNonEmptyForwardOnlyEqualConsecutive)
{
    std::forward_list<int> f = {2, 2, 2, 2};
    EXPECT_EQ(findNEqualConsecutive(f.begin(), f.end(), 4), f.begin());
}

// # findAdjacentEqual
TEST(SearchModule, testfindAdjacentEqualWithEmptyForwardList)
{
    std::forward_list<int> f = {};
    EXPECT_EQ(findAdjacentEqual(f.begin(), f.end()), f.end());
}

TEST(SearchModule, testfindAdjacentEqualWithNonEmptyForwardListNoAdjacentEqual)
{
    std::forward_list<int> f = {1, 2, 3, 7, 2};
    EXPECT_EQ(findAdjacentEqual(f.begin(), f.end()), f.end());
}

TEST(SearchModule, testfindAdjacentEqualWithNonEmptyForwardListOnePair)
{
    std::forward_list<int> f = {2, 2, 3, 4, 5, 6};
    EXPECT_EQ(findAdjacentEqual(f.begin(), f.end()), f.begin());
}

TEST(SearchModule, testfindAdjacentEqualWithNonEmptyForwardManyPairs)
{
    std::forward_list<int> f = {1, 2, 2, 2, 3, 3, 4};
    EXPECT_EQ(findAdjacentEqual(f.begin(), f.end()), ++f.begin());
}

// # findFirstMismatchRandomAccess
TEST(SearchModule, testfindFirstMismatchRandomAccessWithVectorBothEmpty)
{
    std::vector<int> v1;
    std::vector<int> v2;
    auto p = findFirstMismatchRandomAccess(v1.begin(), v1.end(), v2.begin(), v2.end());
    EXPECT_EQ(p.first, v1.end());
    EXPECT_EQ(p.second, v2.end());
}

TEST(SearchModule, testfindFirstMismatchRandomAccessWithVectorDiffSizes)
{
    std::vector<int> v1{1};
    std::vector<int> v2;
    auto p = findFirstMismatchRandomAccess(v1.begin(), v1.end(), v2.begin(), v2.end());
    EXPECT_EQ(p.first, v1.begin());
    EXPECT_EQ(p.second, v2.end());
}

TEST(SearchModule, testfindFirstMismatchRandomAccessWithVectorSameSizeSameElements)
{
    std::vector<int> v1 = {1, 2, 3, 2, 3, 4};
    std::vector<int> v2 = {1, 2, 3, 2, 3, 4};
    ;
    auto p = findFirstMismatchRandomAccess(v1.begin(), v1.end(), v2.begin(), v2.end());
    EXPECT_EQ(p.first, v1.end());
    EXPECT_EQ(p.second, v2.end());
}

TEST(SearchModule, testfindFirstMismatchRandomAccessWithVectorSameSizeDiffElements)
{
    std::vector<int> v1 = {1, 2, 3, 2, 3, 4};
    std::vector<int> v2 = {1, 2, 3, 7, 3, 4};
    ;
    auto p = findFirstMismatchRandomAccess(v1.begin(), v1.end(), v2.begin(), v2.end());
    EXPECT_EQ(*p.first, 2);
    EXPECT_EQ(*p.second, 7);
}

// # findFirstMismatchInput
TEST(SearchModule, testfindFirstMismatchInputWithForwardListBothEmpty)
{
    std::forward_list<int> f1;
    std::forward_list<int> f2;
    auto p = findFirstMismatchInput(f1.begin(), f1.end(), f2.begin(), f2.end());
    EXPECT_EQ(p.first, f1.end());
    EXPECT_EQ(p.second, f2.end());
}

TEST(SearchModule, testfindFirstMismatchInputWithForwardListDiffSizes)
{
    std::forward_list<int> f1{1};
    std::forward_list<int> f2;
    auto p = findFirstMismatchInput(f1.begin(), f1.end(), f2.begin(), f2.end());
    EXPECT_EQ(p.first, f1.begin());
    EXPECT_EQ(p.second, f2.end());
}

TEST(SearchModule, testfindFirstMismatchInputWithForwardListSameSizeSameElements)
{
    std::forward_list<int> f1 = {1, 2, 3, 2, 3, 4};
    std::forward_list<int> f2 = {1, 2, 3, 2, 3, 4};
    ;
    auto p = findFirstMismatchInput(f1.begin(), f1.end(), f2.begin(), f2.end());
    EXPECT_EQ(p.first, f1.end());
    EXPECT_EQ(p.second, f2.end());
}

TEST(SearchModule, testfindFirstMismatchInputWithForwardListSameSizeDiffElements)
{
    std::forward_list<int> f1 = {1, 2, 3, 2, 3, 4};
    std::forward_list<int> f2 = {1, 2, 3, 7, 3, 4};
    ;
    auto p = findFirstMismatchInput(f1.begin(), f1.end(), f2.begin(), f2.end());
    EXPECT_EQ(*p.first, 2);
    EXPECT_EQ(*p.second, 7);
}

// # isSorted
TEST(SearchModule, testisSortedWithEmptyForwardList)
{
    std::forward_list<int> f;
    EXPECT_TRUE(isSorted(f.begin(), f.end()));
}

TEST(SearchModule, testisSortedWithForwardListSorted)
{
    std::forward_list<int> f{1, 2, 3, 4, 5};
    EXPECT_TRUE(isSorted(f.begin(), f.end()));
}

TEST(SearchModule, testisSortedWithForwardListUnSorted)
{
    std::forward_list<int> f{1, 2, 3, 7, 4, 5};
    EXPECT_FALSE(isSorted(f.begin(), f.end()));
}

// # findFirstUnsorted
TEST(SearchModule, testfindFirstUnsortedWithEmptyForwardList)
{
    std::forward_list<int> f;
    EXPECT_EQ(findFirstUnsorted(f.begin(), f.end()), f.end());
}

TEST(SearchModule, testfindFirstUnsortedWithForwardListSorted)
{
    std::forward_list<int> f{1, 2, 3, 4, 5};
    EXPECT_EQ(findFirstUnsorted(f.begin(), f.end()), f.end());
}

TEST(SearchModule, testfindFirstUnsortedWithForwardListUnSorted)
{
    std::forward_list<int> f{1, 2, 3, 7, 4, 5};
    EXPECT_EQ(*findFirstUnsorted(f.begin(), f.end()), 4);
}

// # Partition
TEST(SearchModule, testPartitionEmptyVector)
{
    std::vector<int> v = {};
    EXPECT_NO_FATAL_FAILURE(Partition(v.begin(), v.end(), predicateFunction<int>));
}

TEST(SearchModule, testEvenPartitionNonEmptyVector)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 9, 10};
    EXPECT_NO_FATAL_FAILURE(Partition(v.begin(), v.end(), predicateFunction<int>));
    std::vector<int> result = {2, 4, 6, 10, 1, 3, 5, 7, 9};
    auto it1 = v.begin();
    auto it2 = result.begin();
    while (it1 != v.end())
    {
        ASSERT_EQ(*it1++, *it2++);
    }
}
TEST(SearchModule, testEvenPartitionNonEmptyVectorDuplicates)
{
    std::vector<int> v = {1, 1, 1, 2, 2, 2, 4, 4, 4, 7};
    EXPECT_NO_FATAL_FAILURE(Partition(v.begin(), v.end(), predicateFunction<int>));
    std::vector<int> result = {2, 2, 2, 4, 4, 4, 1, 1, 1, 7};
    auto it1 = v.begin();
    auto it2 = result.begin();
    while (it1 != v.end())
    {
        ASSERT_EQ(*it1++, *it2++);
    }
}

// # partitionAndFindFirstOdd
TEST(SearchModule, testpartitionAndFindFirstOddEmptyVector)
{
    std::vector<int> v = {};
    EXPECT_EQ(partitionAndFindFirstOdd(v.begin(), v.end()), v.end());
}

TEST(SearchModule, testpartitionAndFindFirstOddEmptyVectorIsEven)
{
    std::vector<int> v = {2, 4, 6, 1, 2, 3, 7};
    EXPECT_EQ(*partitionAndFindFirstOdd(v.begin(), v.end()), 1);
}

TEST(SearchModule, testpartitionAndFindFirstOddEmptyVectorNoEven)
{
    std::vector<int> v = {2, 4};
    EXPECT_EQ(partitionAndFindFirstOdd(v.begin(), v.end()), v.end());
}

// # containsSubrange

TEST(SearchModule, testcontainsSubrangeWithEmptySubsequence)
{
    std::forward_list<int> f1 = {1, 4, 6, 7, 8};
    std::forward_list<int> f2 = {};
    EXPECT_TRUE(containsSubrange(f1.begin(), f1.end(), f2.begin(), f2.end()));
}

TEST(SearchModule, testcontainsSubrangeWithEmptySequence)
{
    std::forward_list<int> f1 = {};
    std::forward_list<int> f2 = {1};
    EXPECT_FALSE(containsSubrange(f1.begin(), f1.end(), f2.begin(), f2.end()));
}

TEST(SearchModule, testcontainsSubrangeWithSameSequence)
{
    std::forward_list<int> f1 = {1, 2, 3};
    EXPECT_TRUE(containsSubrange(f1.begin(), f1.end(), f1.begin(), f1.end()));
}

TEST(SearchModule, testcontainsSubrangeWithDiffSubsequenceTrue)
{
    std::forward_list<int> f1 = {1, 2, 3};
    std::forward_list<int> f2 = {2, 3};
    EXPECT_TRUE(containsSubrange(f1.begin(), f1.end(), f2.begin(), f2.end()));
}

TEST(SearchModule, testcontainsSubrangeWithDiffSubsequenceFalse)
{
    std::forward_list<int> f1 = {1, 2, 3};
    std::forward_list<int> f2 = {4, 5};
    EXPECT_FALSE(containsSubrange(f1.begin(), f1.end(), f2.begin(), f2.end()));
}

// #findFirstAboveMean
TEST(SearchModule, testfindFirstAboveMeanEmptyForwardList){
    std::forward_list<int> f = {};
    EXPECT_EQ(findFirstAboveMean(f.begin(), f.end()), f.end());
}

TEST(SearchModule, testfindFirstAboveMeanSortedForwardList){
    std::forward_list<int> f = {1,2,3,4,5};
    EXPECT_EQ(*findFirstAboveMean(f.begin(), f.end()), 4);
}

TEST(SearchModule, testfindFirstAboveMeanUnSortedForwardList){
    std::forward_list<int> f = {10,1,2,3,4,5};
    EXPECT_EQ(*findFirstAboveMean(f.begin(), f.end()), 10);
}

// #findFirstDrop
TEST(SearchModule, testfindfindFirstDropEmptyForwardList){
    std::forward_list<int> f = {};
    EXPECT_EQ(findFirstDrop(f.begin(), f.end()), f.end());
}

TEST(SearchModule, testfindfindFirstDropSortedForwardList){
    std::forward_list<int> f = {1,2,3,4,5};
    EXPECT_EQ(findFirstDrop(f.begin(), f.end()), f.end());
}

TEST(SearchModule, testfindfindFirstDropUnSortedForwardList){
    std::forward_list<int> f = {1,2,3,7,4,5};
    EXPECT_EQ(*findFirstDrop(f.begin(), f.end()), 4);
}


// # findLongestStreak
TEST(SearchModule, testfindLongestStreakEmptyForwardList){
    std::forward_list<int> f = {};
    EXPECT_EQ(findLongestStreak(f.begin(), f.end()), f.end());
}


TEST(SearchModule, testfindLongestStreakForwardListOneLongest){
    std::forward_list<int> f = {1,1,2,2,2,2};
    EXPECT_EQ(findLongestStreak(f.begin(), f.end()), ++(++f.begin()));
}

TEST(SearchModule, testfindLongestStreakForwardListMultipleLongest){
    std::forward_list<int> f = {1,1,1,1,2,2,2,2,4,4,4,4};
    EXPECT_EQ(findLongestStreak(f.begin(), f.end()), f.begin());
}
