#include <gtest/gtest.h>
#include "deque.h"


TEST(DequeModule, isEmptyAfterDefaultContructed)
{
    Deque<int> int_deque;
    EXPECT_EQ(int_deque.size(), 0);
    EXPECT_TRUE(int_deque.empty());
}

TEST(DequeModule, checkSizeAfterEmptyInitializerListConstructor)
{
    Deque<int> int_deque = {};
    EXPECT_EQ(int_deque.size(), 0);
    EXPECT_TRUE(int_deque.empty());
}

TEST(DequeModule, checkSizeAfterInitializerListConstructor)
{
    Deque<int> int_deque = {1, 2, 3, 4, 5};
    EXPECT_EQ(int_deque.size(), 5);
}

TEST(DequeModule, checkElementOrderAfterInitializerListConstructor)
{
    Deque<int> int_deque = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(int_deque[i], i + 1);
    }
}

TEST(DequeModule, testCopyConstructorWithCopyInsertable)
{
    Deque<int> int_deque1 = {1, 2, 3, 4, 5};
    Deque<int> int_deque2 = int_deque1;
    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(int_deque1[i], int_deque2[i]);
    }
}

// TEST(DequeModule, testCopyConstructorWithNoNCopyInsertable)
// {
//     Deque<std::unique_ptr<int>> int_deque1;
//     Deque<std::unique_ptr<int>> int_deque2 = int_deque1;
// }

TEST(DequeModule, testMoveConstuctorWithMoveInsertable)
{
    Deque<int> int_deque1 = {1, 2, 3, 4, 5};
    Deque<int> int_deque2 = std::move(int_deque1);
    ASSERT_TRUE(int_deque1.empty());

    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(int_deque2[i], i + 1);
    }
}

TEST(DequeModule, testCopyAssignmentConstructorWithCopyAssignable)
{
    Deque<int> int_deque1 = {1, 2, 3, 4, 5};
    Deque<int> int_deque2;
    int_deque2 = int_deque1;
    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(int_deque1[i], int_deque2[i]);
    }
}

TEST(DequeModule, testCopyAssignmentConstructorWithItself)
{
    Deque<int> int_deque = {1, 2, 3, 4, 5};
    int_deque = int_deque;
    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(int_deque[i], i + 1);
    }
}

TEST(DequeModule, testMoveAssignmentConstructorWithMoveAssignable)
{
    Deque<int> int_deque1 = {1, 2, 3, 4, 5};
    Deque<int> int_deque2;
    int_deque2 = std::move(int_deque1);
    ASSERT_TRUE(int_deque1.empty());

    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(int_deque2[i], i + 1);
    }
}

TEST(DequeModule, testMoveAssignmentConstructorWithItself)
{
    Deque<int> int_deque = {1, 2, 3, 4, 5};
    int_deque = std::move(int_deque);
    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(int_deque[i], i + 1);
    }
}

TEST(DequeModule, IsEmptyAfterClear)
{
    Deque<int> int_deque = {1, 2, 3, 4, 5};
    int_deque.clear();
    EXPECT_EQ(int_deque.size(), 0);
    EXPECT_TRUE(int_deque.empty());
}

TEST(DequeModule, checkSizeAfterPushFront)
{
    Deque<int> int_deque;

    for (int i = 0; i < 10; i++)
    {
        int_deque.push_front(i + 1);
    }
    EXPECT_EQ(int_deque.size(), 10);
}

TEST(DequeModule, checkElementOrderAfterPushFront)
{
    Deque<int> int_deque;
    for (int i = 0; i < 10; i++)
    {
        int_deque.push_front(i + 1);
    }
    int first_element = 10;

    for (int i = 0; i < 10; i++)
    {
        ASSERT_EQ(int_deque[i], 10 - i);
    }
}

TEST(DequeModule, checkSizeAfterPushBack)
{
    Deque<int> int_deque;

    for (int i = 0; i < 10; i++)
    {
        int_deque.push_back(i + 1);
    }
    EXPECT_EQ(int_deque.size(), 10);
}

TEST(DequeModule, checkElementOrderAfterPushBack)
{
    Deque<int> int_deque;
    for (int i = 0; i < 10; i++)
    {
        int_deque.push_back(i + 1);
    }

    for (int i = 0; i < 10; i++)
    {
        ASSERT_EQ(int_deque[i], i + 1);
    }
}

TEST(DequeModule, popFrontFromNonEmptyDeque)
{
    Deque<int> int_deque = {1, 2};
    int_deque.pop_front();
    EXPECT_EQ(int_deque.size(), 1);
    EXPECT_EQ(int_deque[0], 2);
}

TEST(DequeModule, popFrontFromEmptyDeque)
{
    Deque<int> int_deque;
    EXPECT_NO_FATAL_FAILURE(int_deque.pop_front());
    EXPECT_TRUE(int_deque.empty());
}

TEST(DequeModule, popBackFromNonEmptyDeque)
{
    Deque<int> int_deque = {1, 2};
    int_deque.pop_back();
    EXPECT_EQ(int_deque.size(), 1);
    EXPECT_THROW(int_deque[1], std::out_of_range);
}

TEST(DequeModule, popBackFromEmptyDeque)
{
    Deque<int> int_deque;
    EXPECT_NO_FATAL_FAILURE(int_deque.pop_back());
    EXPECT_TRUE(int_deque.empty());
}

TEST(DequeModule, getFrontFromNonEmptyDeque)
{
    Deque<int> int_deque = {1, 2};
    EXPECT_EQ(int_deque.front(), 1);
}

TEST(DequeModule, getFrontFromEmptyDeque)
{
    Deque<int> int_deque;
    EXPECT_THROW(int_deque.front(), std::out_of_range);
}

TEST(DequeModule, getBackFromNonEmptyDeque)
{
    Deque<int> int_deque = {1, 2};
    EXPECT_EQ(int_deque.back(), 2);
}

TEST(DequeModule, getBackFromEmptyDeque)
{
    Deque<int> int_deque;
    EXPECT_THROW(int_deque.back(), std::out_of_range);
}

TEST(DequeModule, getRandomElementInRange)
{
    Deque<int> int_deque{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++)
    {
        ASSERT_EQ(int_deque[i], i);
    }
}

TEST(DequeModule, getRandomElementOutOfRange)
{
    Deque<int> int_deque{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_THROW(int_deque[10], std::out_of_range);
}

TEST(DequeModule, checkSize)
{
    Deque<int> int_deque{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(int_deque.size(), 10);
}