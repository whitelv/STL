#include "QuickSort.h"

int main()
{
    std::vector<int> v1 = {5, 2, 8, 1, 3, 7, 6};
    quick_sort(v1, v1.size());

    int arr[] = {7,6,5,0,4,3,2,1};
    quick_sort(arr, 8);


    char str[] = "cba";
    quick_sort(str, 3);

    return 0;
}