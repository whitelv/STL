#include "shared_ptr.h"
#include <memory>
#include <iostream>

int main()
{
    int * p = new int(9);

    std::shared_ptr<int> ptr2(p);





    
    Shared_ptr<int> sh1 = make_shared<int>(8);
    Shared_ptr<int> sh2 = sh1;


    std::cout << (sh1 == sh2) << std::endl;
    

    return 0;
}