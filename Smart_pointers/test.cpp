#include <gtest/gtest.h>
#include "shared_ptr.h"

class TestClass
{
public:
    TestClass(int val) : a{val} {}
    int getA() { return a; }

private:
    int a = 5;
};

TEST(SharedPtrModule, testPointerIsNullptrAfterDefaultConstructor)
{
    Shared_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(SharedPtrModule, testStrongIsZeroAfterDefaultConstructor)
{
    Shared_ptr<int> ptr;
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrModule, testPointerAfterParameterConstructor)
{
    int *rptr = new int{3};
    Shared_ptr<int> ptr = Shared_ptr(rptr);
    EXPECT_EQ(rptr, ptr.get());
}

TEST(SharedPtrModule, testStrongAfterParameterConstructor)
{
    Shared_ptr<int> ptr = make_shared<int>(3);
    EXPECT_EQ(ptr.use_count(), 1);
    EXPECT_TRUE(ptr.unique());
}

TEST(SharedPtrModule, testPointerAfterCopyConstructor)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    Shared_ptr<int> ptr1 = ptr;
    EXPECT_EQ(ptr.get(), ptr1.get());
}

TEST(SharedPtrModule, testStrongAfterCopyConstructor)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    Shared_ptr<int> ptr1 = ptr;
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_FALSE(ptr.unique());
}

TEST(SharedPtrModule, testStrongCalculationsWithCopyConstructor)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    {
        Shared_ptr<int> ptr1 = ptr;
        ASSERT_EQ(ptr.use_count(), 2);
        EXPECT_FALSE(ptr.unique());
    }
    ASSERT_EQ(ptr.use_count(), 1);
    EXPECT_TRUE(ptr.unique());
}

TEST(SharedPtrModule, testPointerWithMoveConstructor)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    int *address = ptr.get();
    Shared_ptr<int> ptr1 = std::move(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr1.get(), address);
}

TEST(SharedPtrModule, testStrongWithMoveConstructor)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    Shared_ptr<int> ptr1 = std::move(ptr);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtrModule, testPointerAfterCopyAssignment)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    Shared_ptr<int> ptr1;
    ptr1 = ptr;
    EXPECT_EQ(ptr.get(), ptr1.get());
}

TEST(SharedPtrModule, testStrongAfterCopyAssignment)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    Shared_ptr<int> ptr1;
    ptr1 = ptr;
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_FALSE(ptr.unique());
}

TEST(SharedPtrModule, testCopyAssignmentWithItself)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    ptr = ptr;
    EXPECT_TRUE(ptr.unique());
}

TEST(SharedPtrModule, testPointerWithMoveAssignment)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    int *address = ptr.get();
    Shared_ptr<int> ptr1;
    ptr1 = std::move(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr1.get(), address);
}

TEST(SharedPtrModule, testStrongWithMoveAssignment)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    Shared_ptr<int> ptr1;
    ptr1 = std::move(ptr);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtrModule, testMoveAssignmentWithItself)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    ptr = std::move(ptr);
    EXPECT_TRUE(ptr.unique());
}

TEST(SharedPtrModule, testPoinerIsNullptrAfterResetNoArg)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(SharedPtrModule, testStrongIsZeroAfterResetNoArg)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    ptr.reset();
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrModule, testPoinerIsNewPtrAfterResetNoArg)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    int *r_ptr = new int{4};
    ptr.reset(r_ptr);
    EXPECT_EQ(ptr.get(), r_ptr);
}

TEST(SharedPtrModule, testStrongIsOneAfterResetNoArg)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    ptr.reset(new int{4});
    ASSERT_EQ(ptr.use_count(), 1);
    EXPECT_TRUE(ptr.unique());
}

TEST(SharedPtrModule, testSwapWithDiffStrongValues)
{
    Shared_ptr<int> ptr1 = make_shared<int>(1);
    Shared_ptr<int> ptr2 = make_shared<int>(2);
    Shared_ptr<int> ptr3 = ptr2;

    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr2.use_count(), 2);

    int *add1 = ptr1.get();
    int *add2 = ptr2.get();

    ptr1.swap(ptr2);

    ASSERT_EQ(ptr2.get(), add1);
    ASSERT_EQ(ptr1.get(), add2);

    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrModule, testGetWithEmptyPointer)
{
    Shared_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(SharedPtrModule, testGetWithNoNEmptyPointer)
{
    int *r_ptr = new int{3};
    Shared_ptr<int> ptr = Shared_ptr<int>(r_ptr);
    EXPECT_EQ(ptr.get(), r_ptr);
}

TEST(SharedPtrModule, testDereferencingWithNonEmptyPointer)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    EXPECT_EQ(*ptr, 5);
}

TEST(SharedPtrModule, testArrowOperatorWithNonEmptyPointer)
{
    Shared_ptr<TestClass> ptr = make_shared<TestClass>(5);
    EXPECT_EQ(ptr->getA(), 5);
}

TEST(SharedPtrModule, testUseCountWithEmptyPointer)
{
    Shared_ptr<int> ptr;
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrModule, testUseCountWithNonEmptyPointer)
{
    Shared_ptr<int> ptr = make_shared<int>(5);
    Shared_ptr<int> ptr1 = ptr;
    ASSERT_EQ(ptr.use_count(), 2);
}

TEST(SharedPtrModule, testUniqueWithEmptyPointer)
{
    Shared_ptr<int> ptr;
    EXPECT_FALSE(ptr.unique());
}

TEST(SharedPtrModule, testUniqueWithNonEmptyUniquePointer)
{
    Shared_ptr<int> ptr = make_shared<int>(9);
    EXPECT_TRUE(ptr.unique());
}

TEST(SharedPtrModule, testUniqueWithNonEmptyNonUniquePointer)
{
    Shared_ptr<int> ptr = make_shared<int>(9);
    Shared_ptr<int> ptr1 = ptr;
    EXPECT_FALSE(ptr.unique());
}

TEST(SharedPtrModule, testBoolConversionEmptyPointer)
{
    Shared_ptr<int> ptr;
    EXPECT_FALSE(ptr);
}

TEST(SharedPtrModule, testBoolConversionNonEmptyPointer)
{
    Shared_ptr<int> ptr = make_shared<int>(9);
    EXPECT_TRUE(ptr);
}


TEST(SharedPtrModule, testMakeShared){
    Shared_ptr<int> ptr = make_shared<int>(3);
    EXPECT_TRUE(ptr.unique());
    EXPECT_EQ(*ptr, 3);
}

TEST(SharedPtrModule, testEqualityTrue){
    Shared_ptr<int> ptr = make_shared<int>(3);
    Shared_ptr<int> ptr1 = ptr;
    EXPECT_TRUE((ptr == ptr1));
}

TEST(SharedPtrModule, testEqualityFalse){
    Shared_ptr<int> ptr = make_shared<int>(3);
    Shared_ptr<int> ptr1 = make_shared<int>(2);
    EXPECT_FALSE((ptr == ptr1));
}
