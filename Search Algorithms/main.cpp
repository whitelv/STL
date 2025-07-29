#include <iostream>
#include <vector>
#include <forward_list>
#include "find.h"

int main()
{
    // int arr[] = {1,2,3,4,5,6,7,8};

    // for (size_t i = 1; i < 9; i++)
    // {
    //     std::cout << binary_search(arr, 8, i) << std::endl;
    // }

    //

    // std::vector<int> v{};
    // for (size_t i = 1; i < 6; i++)
    // {
    //     std::cout << binarySearch(v.begin(), v.end(), i) << std::endl;
    // }

    // for (size_t i = 1; i < 6; i++)
    // {
    //     std::cout << linearSearch(v.begin(), v.end(), i) << std::endl;
    // }

    // std::forward_list<int> l{1, 3, 4};

    // for (size_t i = 1; i < 6; i++)
    // {
    //     std::cout << linearSearch(l.begin(), l.end(), i) << std::endl;
    // }

    std::vector<int> v = {1, 2, 3, 4, 4, 4, 4, 6, 7, 9, 10};
    std::cout << TimesNBinary(v.begin(), v.end(), 1);

    auto p = findRange(v.begin(), v.end(), 4);

    std::cout << "First element: " << *p.first << std::endl;
    std::cout << "Second element: " << *(--p.second) << std::endl;

    return 0;
}