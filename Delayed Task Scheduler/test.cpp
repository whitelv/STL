#include "gtest/gtest.h"
#include "scheduler1.h"

using timepoint = std::chrono::time_point<Scheduler::clock>;
using ms = std::chrono::milliseconds;

std::mutex mtx;
std::condition_variable cv;

void push_time(std::vector<timepoint> &vec, size_t size)
{
    vec.push_back(std::chrono::high_resolution_clock::now());
    std::unique_lock<std::mutex> lock(mtx);
    if (vec.size() == size)
    {
        cv.notify_one();
    }
}

bool check_execution_time(const std::vector<timepoint> &vec)
{
    auto it_first = vec.cbegin();
    auto it_second = ++vec.cbegin();

    while (it_second != vec.cend())
    {
        if (*it_first > *it_second)
        {
            return false;
        }

        it_first++;
        it_second++;
    }
    return true;
}

void post_check(timepoint start_point, long delay, size_t tasks_num)
{
    Scheduler s;
    std::vector<timepoint> execution_time;

    for (size_t i = 0; i < tasks_num; i++)
    {
        EXPECT_TRUE(s.post(i, [&]
                           { push_time(execution_time, tasks_num); }, start_point + ms(i * delay)));
    }

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&]
            { return execution_time.size() == tasks_num; });

    EXPECT_EQ(execution_time.size(), tasks_num);
    EXPECT_TRUE(check_execution_time(execution_time));

    EXPECT_EQ(execution_time.size(), tasks_num);
}

TEST(SchedulerModule, ConstuctAndDestoyEmptyScheduler)
{
    EXPECT_NO_FATAL_FAILURE(Scheduler{});
}

TEST(SchedulerModule, testPostTasksWithShortDelayIntoScheduler)
{
    post_check(Scheduler::clock::now(), 5, 10);
}

TEST(SchedulerModule, testPostTasksWithLongDelayIntoScheduler)
{
    post_check(Scheduler::clock::now(), 500, 5);
}

TEST(SchedulerModule, testPostManyTasksIntoScheduler)
{
    post_check(Scheduler::clock::now(), 2, 1000);
}

TEST(SchedulerModule, testPostExpiredTimePointsIntoScheduler)
{
    post_check(Scheduler::clock::now() - ms(2000), 50, 10);
}

TEST(SchedulerModule, testPostOneIntoScheduler)
{
    Scheduler s;
    bool ready = false;
    EXPECT_TRUE(s.post(1, [&]
                       {std::unique_lock<std::mutex> lock(mtx); ready = true; cv.notify_one(); }, Scheduler::clock::now() + ms(1000)));

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&]
            { return ready; });
}

TEST(SchedulerModule, testPostSameIdIntoScheduler)
{
    Scheduler s;
    bool ready = false;
    EXPECT_TRUE(s.post(1, [&]
                       {std::unique_lock<std::mutex> lock(mtx); ready = true; cv.notify_one(); }, Scheduler::clock::now() + ms(100)));
    EXPECT_FALSE(s.post(1, [&] {}, Scheduler::clock::now() + ms(1000)));

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&]
            { return ready; });
}

TEST(SchedulerModule, testPostIntoSchedulerNoTimeToFinishTasks)
{
    std::vector<timepoint> execution_time;
    {
        Scheduler s;
        for (size_t i = 0; i < 10; i++)
        {
            EXPECT_TRUE(s.post(i, [&]
                               { push_time(execution_time, 10); }, Scheduler::clock::now() + ms(100)));
        }
    }
    check_execution_time(execution_time);
}

TEST(SchedulerModule, testShutdownDrainScheduler)
{
    std::vector<timepoint> execution_time;

    Scheduler s;
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_TRUE(s.post(i, [&]
                           { push_time(execution_time, 10); }, Scheduler::clock::now() + ms(100)));
    }
    std::this_thread::sleep_for(ms(200));
    s.shutdown();
    EXPECT_FALSE(s.post(10, [&] {}, Scheduler::clock::now()));

    check_execution_time(execution_time);
}

TEST(SchedulerModule, testShutdownCancelScheduler)
{
    std::vector<timepoint> execution_time;

    Scheduler s;
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_TRUE(s.post(i, [&, i]
                           { push_time(execution_time, 10); }, Scheduler::clock::now() + ms(i * 100)));
    }
    std::this_thread::sleep_for(ms(200));
    s.shutdown(1);

    EXPECT_FALSE(s.post(10, [&] {}, Scheduler::clock::now()));

    check_execution_time(execution_time);
    EXPECT_LT(execution_time.size(), 10);
}


TEST(SchedulerModule, testCancelExistingIdScheduler)
{
    Scheduler s;
    bool ready = false;
    EXPECT_TRUE(s.post(1, [&]
                       {std::unique_lock<std::mutex> lock(mtx); ready = true; cv.notify_one(); }, Scheduler::clock::now() + ms(1000)));

    std::this_thread::sleep_for(ms(100));
    EXPECT_TRUE(s.cancel(1));

    EXPECT_TRUE(s.post(1, [&]
                       {std::unique_lock<std::mutex> lock(mtx); ready = true; cv.notify_one(); }, Scheduler::clock::now() + ms(50)));


    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&]
            { return ready; });
}

TEST(SchedulerModule, testCancelNonExistingIdScheduler)
{
    Scheduler s;
    EXPECT_FALSE(s.cancel(1));
}