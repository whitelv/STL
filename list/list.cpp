#include "list.h"
#include <list>
#include <iostream>


int main(){
    std::cout << "std::list:" << std::endl;



    std::cout << "----------------" << std::endl;
    std::cout << "doubly-linked list:" << std::endl;

    


    List<int> l2 {1,2,5,6,7};
// 
    List<int> l1 {l2.begin(), l2.end()};

    l1.clear();

    l1.display_forward();


    return 0;
}