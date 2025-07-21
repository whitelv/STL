

#include "deque.h"
#include <deque>
#include <iostream>
#include <chrono>




int main(){

    Deque<int> int_deque;

    for (int i = 0; i < 10; i++)
    {
        int_deque.push_front(i + 1);
    }


    int_deque.display();
 

    return 0;
}