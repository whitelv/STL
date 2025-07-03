#include "unique_ptr.h"
#include <memory>
#include <iostream>

int main()
{
    int * a = new int(9);
    std::unique_ptr<int> ptr1(nullptr);
    ptr1.reset(new int(8));
    std::cout << "a: " << *a << std::endl;
    
    int * b = new int(8);
    int o = 8;
    Unique_ptr<int> u = Make_unique<int>(o);
    std::cout << *u << std::endl;
}