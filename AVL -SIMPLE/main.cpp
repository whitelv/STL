#include "avl.h"

int main()
{

    AVL<int, int> t;

    t.insert(100, 1);
    t.insert(50, 1);
    t.insert(25, 1);
    t.insert(75, 1);
    t.insert(90, 1);
    t.insert(60, 1);
    t.insert(150, 1);
    t.insert(200, 1);
    t.insert(300, 1);
    t.insert(400, 1);
    t.insert(500, 1);
    t.insert(600, 1);


    t.erase(75);
    t.erase(300);
    t.erase(400);
    t.erase(600);
    t.erase(60);
    t.erase(100);
    t.erase(25);
    t.erase(50);
    t.erase(500);
    
    

    
    t.display();



    return 0;
}