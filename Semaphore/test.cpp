#include "gtest/gtest.h"
#include "semaphore.h"
#include <thread>
#include <chrono>
#include <vector>


std::mutex mtx;

template <size_t N>
void test(Semaphore<N> & s, int & a, int num){
    s.acquire();
    mtx.lock();
    a += num;
    mtx.unlock();
    s.release();
}

TEST(SemaphoreModule, createSemaphoreMaxGreaterThanDesired)
{
    EXPECT_NO_THROW(Semaphore<3>(2));
}

TEST(SemaphoreModule, createSemaphoreMaxEqualToDesired)
{
    EXPECT_NO_THROW(Semaphore<3>(3));
}

TEST(SemaphoreModule, createSemaphoreLessThanDesiredThrow)
{
    EXPECT_THROW(Semaphore<2>(3), std::out_of_range);
}

TEST(SemaphoreModule, getMaxNumberOfConcurrentThreads)
{
    Semaphore<10> s(4);
    EXPECT_EQ(s.max(), 10);
}

TEST(SemaphoreModule, ReleaseAllAvailableSlotsForConcurrentThreads)
{
    Semaphore<10> s(0);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_NO_THROW(s.release());
    }
    EXPECT_THROW(s.release(), std::out_of_range);
}

TEST(SemaphoreModule, ReleaseNonAvailableSlotsForConcurrentThreads)
{
    Semaphore<10> s(0);
    EXPECT_THROW(s.release(11), std::out_of_range);
}

TEST(SemaphoreModule, AcquireAllAvailableSlotsForConcurrentThreads)
{
    Semaphore<10> s(10);
    ASSERT_THROW(s.release(), std::out_of_range);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_NO_FATAL_FAILURE(s.acquire());
    }
    ASSERT_NO_THROW(s.release(10));
}

TEST(SemaphoreModule, TryAcquireAvailableSlotForConcurrentThread)
{
    Semaphore<10> s(10);
    EXPECT_TRUE(s.try_acquire());
    EXPECT_THROW(s.release(2), std::out_of_range);
}

TEST(SemaphoreModule, TryAcquireNonAvailableSlotForConcurrentThread)
{
    Semaphore<10> s(0);
    EXPECT_FALSE(s.try_acquire());
}

TEST(SemaphoreModule, AllNonAvaliableSlotsFirst){
    Semaphore<10> s(0);
    std::vector<std::thread> threads;

    int a = 0;

    for (size_t i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(test<10>, std::ref(s), std::ref(a), i));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    s.release(10);
    
    for(auto &t : threads){
        t.join();
    }
    EXPECT_EQ(a, 45);
}

TEST(SemaphoreModule, AllAvaliableSlotsFirst){
    Semaphore<10> s(10);
    std::vector<std::thread> threads;

    int a = 0;

    for (size_t i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(test<10>, std::ref(s), std::ref(a), i));
    }
    
    for(auto &t : threads){
        t.join();
    }
    EXPECT_EQ(a, 45);
}


TEST(SemaphoreModule, HalfAvaliableSlotsFirst){
    Semaphore<10> s(5);
    std::vector<std::thread> threads;

    int a = 0;

    for (size_t i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(test<10>, std::ref(s), std::ref(a), i));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    s.release(5);
    
    for(auto &t : threads){
        t.join();
    }
    EXPECT_EQ(a, 45);
}
