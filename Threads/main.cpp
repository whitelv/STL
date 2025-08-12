#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <chrono>

// 1) Hello from a Thread
void hello_from_thread()
{
    std::thread t([]()
                  { std::cout << "hello from thread" << std::endl; });
    t.join();
}

// 2) Multiple Threads Printing
void multiple_threads()
{
    std::vector<std::thread> threads;

    for (size_t i = 0; i < 3; i++)
    {
        std::thread t([i]()
                      { std::cout << "Thread " << i << " started" << std::endl; });
        threads.push_back(std::move(t));
    }

    for (size_t i = 0; i < 3; i++)
    {
        threads[i].join();
    }
}

// 3) Thread Running a Free Function

void printMessage(const std::string &str)
{
    std::cout << str << std::endl;
}

void run_free_function(const std::string &str)
{
    std::thread t(printMessage, std::ref(str));
    t.join();
}

// 4) Thread with Lambda and Delay
void lambda_delay()
{
    std::thread t([]()
                  {
        for (size_t i = 1; i < 6; i++)
        {
            std::cout << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } });

    t.join();
}

// 5) Passing Parameters by Value vs Reference

void passing_by_value_reference()
{
    int counter = 5;
    std::cout << "counter before: " << counter << std::endl;
    std::thread t1([](int a)
                   { a += 1; }, counter);
    t1.join();
    std::cout << "counter after t1: " << counter << std::endl;
    std::thread t2([](int &a)
                   { a += 1; }, std::ref(counter));
    t2.join();
    std::cout << "counter after t2: " << counter << std::endl;
}

// 6) Vector of Threads
void vector_thread()
{
    size_t n;
    std::cout << "Enter n threads: ";
    std::cin >> n;

    std::vector<std::thread> threads;

    for (size_t i = 0; i < n; i++)
    {
        std::thread t([i]()
                      { std::cout << "Thread " << i << " working" << std::endl; });
        threads.push_back(std::move(t));
    }

    for (size_t i = 0; i < n; i++)
    {
        threads[i].join();
    }
}

// 7) Lambda Capture Modes
void lambda_capture_modes(){
    int a = 7;
    int b = 9;
    std::cout << "a before: " << a << std::endl;
    std::cout << "b before: " << b << std::endl;
    std::thread t([b, &a]() mutable{
        b += 1;
        a += 1;
    });

    t.join();

    std::cout << "a after: " << a << std::endl;
    std::cout << "b after: " << b << std::endl;
}

int main()
{
    // hello_from_thread();
    // multiple_threads();
    // run_free_function("message");
    // lambda_delay();
    // passing_by_value_reference();
    // vector_thread();
    // lambda_capture_modes();
}