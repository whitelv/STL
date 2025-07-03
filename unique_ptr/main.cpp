#include "unique_ptr.h"
#include <memory>
#include <iostream>

int main()
{
    {
        int * ptr0 = new int[10];
        ptr0[0] = 9;
        std::unique_ptr<int[]> ptr1(ptr0);
        ptr1.reset();

        int * ptr = new int[10];
        for (size_t i = 0; i < 10; i++)
        {
            ptr[i] = i;
        }
        Unique_ptr<int> p = make_unique<int>(7);
        // Unique_ptr<int[]> ptr2 = make_unique<int[]>(20);

        // for (size_t i = 0; i < 20; i++)
        // {
        //     ptr2[i] = i * 2;
        // }

        // for (size_t i = 0; i < 20; i++)
        // {
        //     std::cout << ptr2[i] << std::endl;
        // }
        // std::cout << std::endl;
        
        


        
    }

    return 0;
}