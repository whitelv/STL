#include "bst.h"



int main(){
    BST<int> t;

    t.insert(10, 7);
    t.insert(7,787);
    t.insert(6, 7);
    t.insert(15, 7);
    t.insert(25, 7);
    t.insert(9, 7);


    t.display();

    return 0;
}