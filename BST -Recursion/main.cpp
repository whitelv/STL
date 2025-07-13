#include "bst.h"



int main(){
    BST<int> t;

    t.insert(50, 7);
    t.insert(25, 7);
    t.insert(10, 7);
    t.insert(40, 7);
    t.insert(45, 7);
    t.insert(100, 7);
    t.insert(150, 7);
    t.insert(200, 7);
    t.insert(300, 7);


    t.erase(50);
    t.erase(150);
    


    t.display();

    return 0;
}