#include "logger.h"
#include <fstream>

int main()
{

    std::ofstream outFile("output.txt");

    
    {
        Logger logger(std::chrono::milliseconds(200000), 1, std::cout);
        std::thread t1([&]()
                       {
        for (size_t i = 0; i < 0; i++)
        {
            logger.log("int" + std::to_string(i) + "\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } });

        std::thread t2([&]()
                       {
        for (size_t i = 0; i < 1; i++)
        {
            logger.log("long" + std::to_string(i) + "\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } });

        std::thread t3([&]()
                       {
        for (size_t i = 0; i < 0; i++)
        {
            logger.log("double" + std::to_string(i) + "\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        } });

        t1.join();
        t2.join();
        t3.join();

    }
    outFile.close();

    return 0;
}