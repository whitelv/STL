#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <memory>
#include <exception>

template <class T>
class Deque
{

    //**Modifiers
public:
    // * clear
    void clear()
    {
        for (size_t i = 0; i < array_counter; i++)
        {
            free(map[map_offset + i]);
        }
        free(map);

        map = allocate_map(map_size);
        size_m = 0;
        map_capacity = map_size;
    }

    // * push___()
    void push_front(const T &value)
    {
        if (size_m == 0)
        {
            first_array();
        }

        if (array_offset == 0)
        {
            if (map_offset == 0)
            {
                // * create new map and copy values
                copy_values();
            }

            // * Create a new array in the beginning
            T *new_array = allocate_array();
            array_offset = array_size;
            array_counter++;

            map[--map_offset] = new_array;
        }

        // * add value to array
        map[map_offset][--array_offset] = value;
        ++size_m;
    }

    void push_back(const T &value)
    {
        if (size_m == 0)
        {
            first_array();
        }

        // * calculate position of element
        size_t arr_pos = calc_arr_pos();
        size_t map_pos = calc_map_pos();

        if (arr_pos == 0)
        {
            if (map_pos == map_capacity - 1)
            {
                // * create new map and copy values
                copy_values();
            }

            // * recalculate map position of element
            map_pos = calc_map_pos();

            // * Create a new array in the end
            T *new_array = allocate_array();
            array_counter++;
            map[++map_pos] = new_array;
        }

        // * add value to array
        map[map_pos][arr_pos] = value;
        size_m++;
    }

    // * pop____()
    void pop_front()
    {
        if (size_m == 0)
        {
            return;
        }

        // * call destructor
        std::destroy_at(&map[map_offset][array_offset]);
        size_m--;
        array_offset = (array_offset + 1) % array_size;

        // * delete array memory
        if (array_offset == 0 || size_m == 0)
        {
            free(map[map_offset]);
            map_offset++;
            array_counter--;
        }
    }

    void pop_back()
    {
        if (size_m == 0)
        {
            return;
        }
        // * calc pos of the last element
        size_t arr_pos = calc_last_pos();
        size_t map_pos = calc_map_pos();

        // * call destructor
        std::destroy_at(&map[map_pos][arr_pos]);
        map[map_pos][arr_pos] = -1;
        size_m--;

        // * delete array memory
        if (arr_pos == 0 || size_m == 0)
        {
            free(map[map_pos]);
            array_counter--;
        }
    }

    // ** Element access
public:
    T &front()
    {
        if (size_m == 0)
        {
            throw std::out_of_range("Cannot access an element");
        }
        return map[map_offset][array_offset];
    }
    const T &front() const
    {
        if (size_m == 0)
        {
            throw std::out_of_range("Cannot access an element");
        }
        return map[map_offset][array_offset];
    }

    T &back()
    {
        if (size_m == 0)
        {
            throw std::out_of_range("Cannot access an element");
        }
        size_t arr_pos = calc_last_pos();
        size_t map_pos = calc_map_pos();
        return map[map_pos][arr_pos];
    }

    const T &back() const
    {
        if (size_m == 0)
        {
            throw std::out_of_range("Cannot access an element");
        }
        size_t arr_pos = calc_last_pos();
        size_t map_pos = calc_map_pos();
        return map[map_pos][arr_pos];
    }

    T &operator[](size_t index)
    {
        double number = double(index) / array_size + array_offset / double(array_size);

        double intPart;
        double fracPart = std::modf(number, &intPart);

        size_t map_index = map_offset + intPart;
        size_t arr_index = fracPart * array_size;

        return map[map_index][arr_index];
    }

    // ** Capacity
public:
    size_t size() { return size_m; };
    size_t capacity() { return map_capacity; };


    // ** Constructor & Destructor
public:
    Deque() : map{allocate_map(map_size)}, size_m{0}, map_capacity{map_size}, array_counter{0}{}

    ~Deque()
    {
        for (size_t i = 0; i < array_counter; i++)
        {
            free(map[map_offset + i]);
        }
        free(map);
    }

    // ** Helper functions
private:
    T *allocate_array()
    {
        return (T *)malloc(array_size * sizeof(T));
    }
    T **allocate_map(size_t size)
    {
        return (T **)malloc(size * sizeof(T *));
    }

    size_t calc_arr_pos()
    {
        return (size_m - (array_size - array_offset)) % array_size;
    }

    size_t calc_last_pos()
    {
        return calc_arr_pos() == 0 ? array_size - 1 : calc_arr_pos() - 1;
    }

    size_t calc_map_pos()
    {
        return map_offset + array_counter - 1;
    }

    void copy_values()
    {
        // * Create new_map with greater capacity
        map_capacity = array_counter * multiplier;
        T **new_map = allocate_map(map_capacity);
        // * calc new offset
        size_t new_map_offset = array_counter - array_counter / 2;
        size_t temp = new_map_offset;

        // * copying values from old map to a new one
        for (size_t i = map_offset; i < map_offset + array_counter; i++)
        {
            new_map[temp++] = map[i];
        }

        // * delete old map
        free(map);
        map = new_map;
        map_offset = new_map_offset;
    }

    void first_array()
    {
        map_offset = map_capacity / 2;
        array_offset = array_size / 2;

        T *array = allocate_array();
        array_counter = 1;
        map[map_offset] = array;
    }

    // ! only for studying purposes
    void display() const
    {
        for (size_t i = map_offset; i < map_offset + array_counter; i++)
        {
            std::cout << "Map_offset " << i << ": ";
            for (size_t j = 0; j < array_size; j++)
            {
                std::cout << map[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    T **map;
    size_t size_m;
    size_t map_offset;
    size_t array_offset;
    size_t array_counter;
    size_t map_capacity;

    static const int multiplier = 2;
    static const int map_size = 4;
    static const int array_size = 4;
};

#endif