#include "bst.h"



int main(){
    BST<int> t;

    t.insert(10, 1);
    t.insert(15, 2);
    t.insert(14, 3);
    t.insert(6, 4);
    t.insert(17, 5);
    t.insert(8, 6);
    t.insert(3, 7);
    t.insert(13, 8);

    t.erase(10);
    t.erase(3);
    t.erase(14);
    t.display();
}