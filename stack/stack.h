#ifndef STACK_H
#define STACK_H

#include "../deque/deque.h"

template <typename T>
class Stack
{
    // ** Element access
public:
    T &top() { return stack.back(); }
    const T &top() const { return stack.back(); }

    // ** Capacity
public:
    size_t size() const { return stack.size(); }
    bool empty() const { return stack.empty(); }

    // ** Modifiers
public:
    void push(const T &value) { stack.push_back(value); }
    void pop() { stack.pop_back(); }

    // ** Constructor & Destructor
public:
    Stack() {};
    ~Stack() {};

public:
    Deque<T> stack;
};

#endif