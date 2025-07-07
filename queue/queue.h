#ifndef QUEUE_H
#define QUEUE_H

#include "../deque/deque.h"

template <typename T>
class Queue
{

    // ** Element access
public:
    T &front() { return q.front(); }
    const T &front() const { return q.front(); }

    T &back() { return q.back(); }
    const T &back() const { return q.back(); }

    // ** Capacity
public:
    size_t size() const { return q.size(); }
    bool empty() const { return q.empty(); }

    // ** Modifiers
public:
    void push(const T &value) { q.push_back(value); }
    void pop() { q.pop_front(); }

    // ** Constructor & Destructor
public:
    Queue() {}
    ~Queue() {}

public:
    Deque<T> q;
};

#endif