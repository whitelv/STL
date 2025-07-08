#include "queue.h"


int main(){
    Queue<int> q;

    for (size_t i = 0; i < 15; i++)
    {
        q.push(i + 1);
    }

    Queue<int> q1 = std::move(q);




    std::cout << "Is empty: " << q.empty() << std::endl;
    
    return 0;
}