#include <gtest/gtest.h>
#include "weak_ptr.h"
#include "shared_ptr.h"

TEST(WeakPtrModule, testControlBlockIsNullptrAfterDefaulConstructor)
{
    Weak_ptr<int> w_ptr;
    EXPECT_EQ(w_ptr.use_count(), 0);
}

TEST(WeakPtrModule, testStrongAfterParameterConstructor)
{
    Weak_ptr<int> w_ptr;
    {
        Shared_ptr<int> sh_ptr = make_shared<int>(5);
        w_ptr = Weak_ptr<int>(sh_ptr);
        ASSERT_EQ(w_ptr.use_count(), 1);
    }
    EXPECT_EQ(w_ptr.use_count(), 0);
}

TEST(WeakPtrModule, testStrongAfterCopyConstructor)
{
    Shared_ptr<int> sh_ptr = make_shared<int>(5);
    Shared_ptr<int> sh_ptr2 = sh_ptr;

    Weak_ptr<int> w_ptr1 = Weak_ptr<int>(sh_ptr);
    Weak_ptr<int> w_ptr2 = w_ptr1;

    EXPECT_EQ(w_ptr1.use_count(), w_ptr2.use_count());
}

TEST(WeakPtrModule, testStrongAfterMoveConstructor)
{
    Shared_ptr<int> sh_ptr = make_shared<int>(5);
    Weak_ptr<int> w_ptr1 = Weak_ptr<int>(sh_ptr);
    Weak_ptr<int> w_ptr2 = std::move(w_ptr1);

    EXPECT_EQ(w_ptr1.use_count(), 0);
    EXPECT_EQ(w_ptr2.use_count(), 1);
}

TEST(WeakPtrModule, testStrongAfterCopyAssignment)
{
    Shared_ptr<int> sh_ptr = make_shared<int>(5);
    Weak_ptr<int> w_ptr1 = Weak_ptr<int>(sh_ptr);

    Weak_ptr<int> w_ptr2;
    w_ptr2 = w_ptr1;

    EXPECT_EQ(w_ptr1.use_count(), w_ptr2.use_count());
}

TEST(WeakPtrModule, testStrongAfterMoveAssignment)
{
    Shared_ptr<int> sh_ptr = make_shared<int>(5);
    Weak_ptr<int> w_ptr1 = Weak_ptr<int>(sh_ptr);
    Weak_ptr<int> w_ptr2;
    w_ptr2 = std::move(w_ptr1);

    EXPECT_EQ(w_ptr1.use_count(), 0);
    EXPECT_EQ(w_ptr2.use_count(), 1);
}

TEST(WeakPtrModule, testStrongAfterReset)
{
    Shared_ptr<int> sh_ptr = make_shared<int>(5);
    Weak_ptr<int> w_ptr = Weak_ptr<int>(sh_ptr);

    ASSERT_EQ(w_ptr.use_count(), 1);

    w_ptr.reset();
    EXPECT_EQ(w_ptr.use_count(), 0);
}

TEST(WeakPtrModule, testSwapWithDiffStrongValues)
{
    Shared_ptr<int> sh_ptr = make_shared<int>(5);
    Weak_ptr<int> w_ptr1 = Weak_ptr<int>(sh_ptr);
    ASSERT_EQ(w_ptr1.use_count(), 1);

    Weak_ptr<int> w_ptr2;
    ASSERT_EQ(w_ptr2.use_count(), 0);

    w_ptr1.swap(w_ptr2);

    EXPECT_EQ(w_ptr1.use_count(), 0);
    EXPECT_EQ(w_ptr2.use_count(), 1);
}

TEST(WeakPtrModule, testUseCountWithNonEmptyPointer)
{
    Shared_ptr<int> sh_ptr1 = make_shared<int>(5);
    Shared_ptr<int> sh_ptr2 = sh_ptr1;
    Shared_ptr<int> sh_ptr3 = sh_ptr2;

    Weak_ptr<int> w_ptr = Weak_ptr<int>(sh_ptr1);
    EXPECT_EQ(w_ptr.use_count(), 3);
}

TEST(WeakPtrModule, testExpiredBeforeObjectExpired)
{
    Shared_ptr<int> sh_ptr = make_shared<int>(5);
    Weak_ptr<int> w_ptr = Weak_ptr<int>(sh_ptr);

    EXPECT_FALSE(w_ptr.expired());
}

TEST(WeakPtrModule, testExpiredAfterObjectExpired)
{
    Weak_ptr<int> w_ptr;
    {
        Shared_ptr<int> sh_ptr = make_shared<int>(5);
        w_ptr = Weak_ptr<int>(sh_ptr);
    }

    EXPECT_TRUE(w_ptr.expired());
}

TEST(WeakPtrModule, testLockWithEmtyPointer){
    Weak_ptr<int> w_ptr;
    Shared_ptr<int> sh_ptr = w_ptr.lock();
    EXPECT_EQ(sh_ptr.use_count(), 0);
}

TEST(WeakPtrModule, testLockWithNonPointer){
    Shared_ptr<int> sh_ptr1 = make_shared<int>(5);
    Weak_ptr<int> w_ptr = Weak_ptr<int>(sh_ptr1);

    Shared_ptr<int> sh_ptr2 = w_ptr.lock();
    EXPECT_EQ(sh_ptr1.get(), sh_ptr2.get());
    EXPECT_EQ(sh_ptr1.use_count(), sh_ptr2.use_count());

}

