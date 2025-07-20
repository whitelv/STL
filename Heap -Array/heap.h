#ifndef HEAP_H
#define HEAP_H

#include "../vector/vector.h"
#include <iostream>
#include <queue>
#include <cmath>

template <typename T>
class Heap
{
    // ** public functions
public:
    Heap() : heap{} {};
    ~Heap(){};

    // # insert
    void insert(const T &value)
    {
        heap.push_back(value);

        size_t value_index = heap.Size() - 1;
        heapify_up(value_index);
    }

    // # erase
    void erase_element(size_t index)
    {
        if (index >= heap.Size())
        {
            throw std::out_of_range("Error: cannot delete from nothing");
        }
        std::swap(heap[index], heap[heap.Size() - 1]);
        heap.pop_back();
        heapify_down(index);
    }

    // # removeMin
    void removeMin()
    {
        erase_element(0);
    }

    // # change_value
    void change_value(size_t index, const T &value){
        if (index >= heap.Size())
        {
            throw std::out_of_range("Error: cannot access nothing");
        }
        T prev_value = heap[index];
        heap[index] = value;

        if (value < prev_value)
        {
            heapify_up(index);
            return;
        }
        heapify_down(index);
    }

    // #display
    void display() const
    {
        auto it = heap.cbegin();
        while (it != heap.cend())
        {
            std::cout << "[ " << *it++ << " ], " << std::flush;
        }
        std::cout << std::endl;
    }

    const T * get_min() const{
        return !heap.empty() ? heap.data() : nullptr;
    }

    

    // ** helper functions
private:
    // # heapify_up
    void heapify_up(size_t index)
    {
        if (index == 0)
        {
            return;
        }
        size_t p_index = parent(index);
        if (heap[index] < heap[p_index])
        {
            std::swap(heap[p_index], heap[index]);
            heapify_up(p_index);
        }
        return;
    }

    // # heapify_down
    void heapify_down(size_t p_index)
    {
        size_t lch_index = left_child(p_index);
        size_t rch_index = right_child(p_index);
        size_t smallest = p_index;

        if (check_child(lch_index) && heap[lch_index] < heap[smallest])
        {
            smallest = lch_index;
        }

        if (check_child(rch_index) && heap[rch_index] < heap[smallest])
        {
            smallest = rch_index;
        }

        if (smallest != p_index)
        {
            std::swap(heap[p_index], heap[smallest]);
            heapify_down(smallest);
        }
    }
    // # children & parent indexes
    size_t left_child(size_t p_index)
    {
        return 2 * p_index + 1;
    }

    size_t right_child(size_t p_index)
    {
        return 2 * p_index + 2;
    }

    bool check_child(size_t ch_index)
    {
        return ch_index < heap.Size();
    }

    size_t parent(size_t ch_index)
    {
        return (ch_index - 1) / 2;
    }

    
    // ** class members
private:
    Vector<T> heap;
};

#endif