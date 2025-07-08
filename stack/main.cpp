#include "stack.h"

int main()
{
    Stack<int> s;

    for (size_t i = 0; i < 10; i++)
    {
        s.push(i);
    }

    Stack<int> s1;
    s1 = std::move(s);


    
    s1.push(100);

    s.push(90);

    s.stack.display();

    std::cout << std::endl;
    s1.stack.display();


    
    return 0;
}