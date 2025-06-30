//
//  array.cpp
//  STL
//
//  Created by Любомир Витвицький on 24.06.2025.
//

#include <iostream>
#include <vector>
#include "vector.h"



template<typename... Args>
void function(Args&&... args) {
//    constexpr size_t count = sizeof...(Args);  // Кількість типів
    // або
    constexpr size_t count = sizeof...(args);  // Кількість аргументів
    
    std::cout << "Кількість аргументів: " << count << std::endl;
}

class hello{
    public:
            int a;
            int b;
            int c;
    hello(int a, int b, int c) : a(a), b(b), c(c){};
    hello(){};
};




int main(){
    

    
    
    function(1,2,3,4);
    
    
    std::vector<int> v{1,2,3,4,5};
    
    v.insert(v.begin(), {1,2,3,4,5,6});
    
    std::cout << v.size() << " " << v.capacity() << std::endl;



    
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i]  << std::endl;
    }
    
    
    
    

    
    
    
    std::cout << "--------------------------" << std::endl;
    
    Vector<int> v1 = {1,2,3,4,5};
    Vector<int> v2;
    v2 = {1,2,3,4};
    
   
  
    
    for (int i = 0; i < v2.size; i++) {
        std::cout << v2[i] << "    ";
    }
    std::cout << std::endl;
    
}
