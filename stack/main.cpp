#include "stack.h"

int main()
{
    Stack<int> s;

    for (size_t i = 0; i < 10; i++)
    {
        s.push(i);
    }
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    for (size_t i = 0; i < 10; i++)
    {
        s.push(i);
    }
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    std::cout << "IS EMPTY: " << s.empty() << std::endl;

    return 0;
}