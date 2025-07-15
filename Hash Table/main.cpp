#include "hash.h"
#include <forward_list>







int main(){
    Hash_table<int, int> hash_table;
    hash_table.insert(0, 0);
    hash_table.insert(5, 5);
    hash_table.insert(10, 10);
    hash_table.insert(15, 15);


    hash_table.insert(1, 1);
    hash_table.insert(2, 2);


    hash_table.erase(5);
    hash_table.erase(15);


    hash_table.insert(5, 5);
    hash_table.insert(3, 3);
    hash_table.insert(4, 3);
    hash_table.insert(100, 100);


    std::cout << *hash_table.find(10) << std::endl;


    hash_table.display();



    return 0;
}