#ifndef HASH_H
#define HASH_H

#include "../vector/vector.h"
#include <functional>
#include <iostream>
#include <forward_list>

template <typename U, typename T>
class Hash_table
{
private:
    struct Node
    {
        U key;
        T value;
    };

// # Constructor & Destructor
public:
    Hash_table() : map{start_size, nullptr}, current_fill{0} {}
    ~Hash_table()
    {
        for (size_t i = 0; i < map.Size(); i++)
        {
            if (map[i])
            {
                auto begin = map[i]->begin();
                auto end = map[i]->end();
                Node *node;

                while (begin != end)
                {
                    node = *begin++;
                    delete node;
                }
                delete map[i];
            }
        }
    }

    // # Modifiers
public:
    void insert(const U &key, const T &value)
    {
        insert_node(map, key, value);

        if (current_fill / double(map.Size()) > max_fill_rate)
        {
            reallocate_map();
        }
    }

    void erase(const U &key)
    {
        size_t index = hash(key) % map.Size();
        if (map[index] == nullptr)
        {
            return;
        }
        auto before_current = map[index]->before_begin();
        auto current = map[index]->begin();
        auto end = map[index]->end();

        while (current != end)
        {
            Node *node = *current;
            if (node->key == key)
            {
                map[index]->erase_after(before_current);
                delete node;
                return;
            }
            current++;
            before_current++;
        }
    }

    // # Observers
public:
    void display() const
    {
        for (size_t i = 0; i < map.Size(); i++)
        {
            if (map[i])
            {
                auto it = map[i]->begin();
                std::cout << i << ": ";
                while (it != map[i]->end())
                {
                    Node *node = *it++;
                    std::cout << "[ " << node->key << " : " << node->value << " ], ";
                }
                std::cout << std::endl;
            }
        }
    }

    T *find(const U &key)
    {
        size_t index = hash(key) % map.Size();
        if (map[index] == nullptr)
        {
            return nullptr;
        }

        auto begin = map[index]->begin();
        auto end = map[index]->end();
        Node *node;

        while (begin != end)
        {
            node = *begin++;
            if (node->key == key)
            {
                return &node->value;
            }
        }
        return nullptr;
    }

    // # Helpre function
private:
    void insert_node(Vector<std::forward_list<Node *> *> &map, const U &key, const T &value)
    {
        size_t index = hash(key) % map.Size();
        if (map[index] == nullptr)
        {
            map[index] = new std::forward_list<Node *>;
            current_fill += 1;
        }
        map[index]->push_front(new Node{key, value});
    }

    void reallocate_map()
    {
        Vector<std::forward_list<Node *> *> temp_map(map.Size() * multiplier, nullptr);
        current_fill = 0;
        for (size_t i = 0; i < map.Size(); i++)
        {
            if (map[i])
            {
                auto begin = map[i]->begin();
                auto end = map[i]->end();
                Node *node;

                while (begin != end)
                {
                    node = *begin++;
                    insert_node(temp_map, node->key, node->value);
                    delete node;
                }
                delete map[i];
            }
        }
        map = std::move(temp_map);
    }

public:
    Vector<std::forward_list<Node *> *> map;
    size_t current_fill;
    std::hash<U> hash;

    static const size_t start_size = 5;
    static constexpr double max_fill_rate = 0.5;
    static const size_t multiplier = 2;
};

#endif