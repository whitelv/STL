#ifndef CONTROL_H
#define CONTROL_H
#include <cstddef>


template <typename T>
struct control_block
{
    size_t strong;
    size_t weak;
    T * pointer;
};



#endif