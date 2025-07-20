#include "avl.h"

int main()
{
    AVL<int, int> t;

    t.insert(50,3);
    t.insert(100,3);
    t.insert(75,3);
    t.insert(150,3);
    t.insert(200,3);
    t.insert(125,3);
    t.insert(25,3);
    t.insert(5,3);
    t.insert(30,3);
    t.insert(2,3);
    t.insert(1,3);
    t.insert(7,3);
    
    t.erase(1);
    t.erase(25);
    t.erase(7);
    t.erase(2);
    t.erase(125);
    t.erase(200);
    t.erase(50);
    t.erase(30);
    t.erase(100);
    
    
    t.display();

    return 0;
}