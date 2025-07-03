#include "list.h"
#include <list>
#include <iostream>
#include <vector>


int main(){
    std::cout << "std::list:" << std::endl;



    std::cout << "----------------" << std::endl;
    std::cout << "doubly-linked list:" << std::endl;



    List<int> l2 {1,2,3};



    List<int> l1(l2.begin(), l2.end());



    l1.display_forward();
    l1.erase(l1.begin(), l1.end());
    l1.push_back(9);
    l1.push_front(7);
    
    l1.display_forward();
    l1.display_backward();


    std::cout << l1.size() << std::endl;
    

    // l1.clear();

    l1.display_forward();
    l2.display_forward();
    l2.display_backward();


    return 0;
}