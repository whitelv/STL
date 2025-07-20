#include "heap.h"

int main()
{
    Heap<int> h;

    h.insert(0);
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.insert(4);
    h.insert(5);
    h.insert(6);

    h.erase(1);
    h.erase(5);
    h.erase(0);
    h.erase(1);
    h.erase(1);
    h.erase(1);
    h.erase(0);

    h.insert(0);
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.insert(4);
    h.insert(5);
    h.insert(6);


    h.change_value(0, 9);
    h.change_value(5, 0);

    h.clear();

    h.insert(0);
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.insert(4);
    h.insert(5);
    h.insert(6);


    h.display();
}