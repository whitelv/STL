#include "queue.h"


int main(){
    Queue<int> q;

    for (size_t i = 0; i < 15; i++)
    {
        q.push(i + 1);
    }

    for (size_t i = 0; i < 15; i++)
    {
        q.pop();
    }

    for (size_t i = 0; i < 15; i++)
    {
        q.push(i + 1);
    }
    
    for (size_t i = 0; i < 15; i++)
    {
        
        std::cout << q.front() << " ";
        q.pop();
        
    }
    std::cout << std::endl;


    std::cout << "Is empty: " << q.empty() << std::endl;
    
    return 0;
}