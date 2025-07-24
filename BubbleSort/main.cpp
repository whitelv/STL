#include "bubble.h"
#include <vector>

template <typename T>
void display(const T &con, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << con[i] << " " << std::flush;
    }
    std::cout << std::endl;
}

int main()
{
    int arr[7] = {7, 1, 2, 3, 4, 5, 6};
    char * str = new char[4];
    std::strcpy(str, "cba");

    BubbleSort(str, 3);

    display(str, 3);
}