#include "gtest/gtest.h"
#include "mpmc.h"

void push_helper(MPMCQueue<int> &mpmc, int id, int counter)
{
    for (size_t i = 0; i < counter; i++)
    {
        mpmc.push(i * id);
    }
};

void pop_helper(MPMCQueue<int> &mpmc, int counter)
{
    for (size_t i = 0; i < counter; i++)
    {
        mpmc.pop();
    }
};

TEST(MPMCModule, ConstuctMPMCQueue)
{
    MPMCQueue<int> mpmc(10);
    EXPECT_EQ(mpmc.max_capacity(), 10);
    EXPECT_EQ(mpmc.size(), 0);
    EXPECT_TRUE(mpmc.empty());
}

TEST(MPMCModule, pushToMPMCQueue)
{
    MPMCQueue<int> mpmc(10);
    for (size_t i = 0; i < 10; i++)
    {
        mpmc.push(i);
        ASSERT_EQ(mpmc.back(), i);
    }
    EXPECT_EQ(mpmc.size(), 10);
}

TEST(MPMCModule, pushToMPMCQueueMultipleThreads)
{
    MPMCQueue<int> mpmc(10);

    int test = 0;
    int result = 0;

    std::thread t1(push_helper, std::ref(mpmc), 1, 5);
    std::thread t2(push_helper, std::ref(mpmc), 2, 5);

    t1.join();
    t2.join();

    while (!mpmc.empty())
    {
        test += mpmc.front();
        mpmc.pop();
    }

    for (size_t i = 0; i < 5; i++)
    {
        result += i;
        result += i * 2;
    }

    EXPECT_EQ(test, result);
    EXPECT_TRUE(mpmc.empty());
}

TEST(MPMCModule, popFromMPMCQueue)
{
    MPMCQueue<int> mpmc(10);
    for (size_t i = 0; i < 10; i++)
    {
        mpmc.push(i);
        ASSERT_EQ(mpmc.back(), i);
    }

    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_EQ(mpmc.front(), i);
        mpmc.pop();
    }

    EXPECT_EQ(mpmc.size(), 0);
    EXPECT_TRUE(mpmc.empty());
}

TEST(MPMCModule, PopFromMPMCQueueMultipleThreads)
{
    MPMCQueue<int> mpmc(10);

    std::thread t1(push_helper, std::ref(mpmc), 1, 5);
    std::thread t2(push_helper, std::ref(mpmc), 2, 5);

    std::thread t3(pop_helper, std::ref(mpmc), 5);
    std::thread t4(pop_helper, std::ref(mpmc), 5);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    EXPECT_EQ(mpmc.size(), 0);
    EXPECT_TRUE(mpmc.empty());
}

TEST(MPMCModule, tryPushToMPMCQueue)
{
    MPMCQueue<int> mpmc(10);
    EXPECT_TRUE(mpmc.try_push(-1));
    for (size_t i = 0; i < 9; i++)
    {
        mpmc.push(i);
        ASSERT_EQ(mpmc.back(), i);
    }
    EXPECT_FALSE(mpmc.try_push(9));
}

TEST(MPMCModule, tryPopFromMPMCQueue)
{
    MPMCQueue<int> mpmc(10);
    EXPECT_FALSE(mpmc.try_pop());
    for (size_t i = 0; i < 10; i++)
    {
        mpmc.push(i);
        ASSERT_EQ(mpmc.back(), i);
    }
    EXPECT_TRUE(mpmc.try_pop());
}

TEST(MPMCModule, PushForToMPMCQueue)
{
    MPMCQueue<int> mpmc(1);
    mpmc.push(1);
    std::thread t1([&mpmc]()
                   { EXPECT_FALSE(mpmc.push_for(2, std::chrono::milliseconds(50))); });

    std::thread t2([&mpmc]()
                   { EXPECT_TRUE(mpmc.push_for(3, std::chrono::milliseconds(300))); });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread t3([&mpmc]()
                   { mpmc.pop(); });

    t1.join();
    t2.join();
    t3.join();

    EXPECT_EQ(mpmc.front(), 3);
}

TEST(MPMCModule, PopForFromMPMCQueue)
{
    MPMCQueue<int> mpmc(1);
    std::thread t1([&mpmc]()
                   { EXPECT_FALSE(mpmc.pop_for(std::chrono::milliseconds(50))); });

    std::thread t2([&mpmc]()
                   { EXPECT_TRUE(mpmc.pop_for(std::chrono::milliseconds(300))); });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread t3([&mpmc]()
                   { mpmc.push(1); });

    t1.join();
    t2.join();
    t3.join();

    EXPECT_TRUE(mpmc.empty());
}

TEST(MPMCModule, CloseMPMCQueue)
{
    MPMCQueue<int> mpmc(10);
    mpmc.close();
    push_helper(mpmc, 1, 10);
    EXPECT_EQ(mpmc.size(), 0);
    EXPECT_TRUE(mpmc.empty());
}


