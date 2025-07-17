#include "heap.h"

int main()
{
    Heap<int> h;

    h.insert(42);
    h.insert(17);
    h.insert(88);
    h.insert(5);
    h.insert(63);
    h.insert(29);
    h.insert(97);
    h.insert(14);
    h.insert(76);
    h.insert(31);
    h.insert(90);
    h.insert(3);
    h.insert(50);
    h.insert(68);
    h.insert(24);
    h.insert(81);
    h.insert(10);
    h.insert(36);
    h.insert(7);
    h.insert(92);
    h.insert(58);
    h.insert(12);
    h.insert(39);
    h.insert(66);
    h.insert(25);
    
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();
    h.removeMin();

    h.erase_element(1);
    h.erase_element(2);
    h.erase_element(1);


    h.change_value(3, 5);
    h.change_value(0, 100);

    h.display();

    return 0;
}