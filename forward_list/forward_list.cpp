//
//  array.cpp
//  STL
//
//  Created by Любомир Витвицький on 24.06.2025.
//

#include <iostream>
#include <forward_list>
#include "forward_list.h"

template <typename T>
struct Node{
    T value;
    Node * next;
};

template <typename T>
void display(const std::forward_list<T> & a){
    for (const int &x : a) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}


int main(){
    std::cout << "-------STL class:--------" << std::endl;
    
    std::forward_list<int> a{1,2,3,4,5};
    std::forward_list<int> b{1,2,7,4,5};
    
    a.merge(b);
    
    
    display(a);
    
    
    std::cout << "-------------------------" << std::endl;
    
    
    std::cout << "------Custom class:------" << std::endl;
    

    return 0;
    
    
    
    

}
