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
    
    
    
    Forward_list<int> f1 {4,1,24};
    
    std::vector p {1,2,3,45,6,788,90,9,9};
    
    Forward_list<int> f2 {1,7,2,2,2,3,3,4,4};
    
    std::cout << f2.front() << std::endl;
        
    f2.display();

    return 0;
    
    
    
    

}
