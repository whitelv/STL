#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <utility>
#include <iostream>
#include <initializer_list>
#include <exception>
#include <concepts>

template <typename T>
class List
{

    // * Node
private:
    struct Node
    {
        T value;
        Node *prev;
        Node *next;
    };

    Node *create_new_node(const T &value)
    {
        return new Node{value, nullptr, nullptr};
    }

    Node *create_new_node(T &&value)
    {
        return new Node{std::move(value), nullptr, nullptr};
    }

    Node *create_new_sentiel()
    {
        Node *new_node = new Node;
        new_node->next = new_node;
        new_node->prev = new_node;
        return new_node;
    }

private:
    class BiDirectIterator
    {
        // * // Iterator traits
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        // * constructor
    public:
        BiDirectIterator() : node{nullptr} {};
        BiDirectIterator(Node *n, Node *s) : node{n}, sentinel{s} {};
        BiDirectIterator(const BiDirectIterator &b) = default;

        // * operators overloading
    public:
        BiDirectIterator &operator=(const BiDirectIterator &b) = default;
        bool operator==(const BiDirectIterator &b) const { return node == b.node; }
        bool operator!=(const BiDirectIterator &b) const { return node != b.node; }

        T &operator*()
        {
            if (node == sentinel || node == nullptr)
            {
                throw std::out_of_range("Cannot dereference");
            }
            return node->value;
        }
        const T &operator*() const
        {
            if (node == sentinel || node == nullptr)
            {
                throw std::out_of_range("Cannot dereference");
            }
            return node->value;
        }

        T *operator->()
        {
            if (node == sentinel || node == nullptr)
            {
                throw std::out_of_range("Cannot dereference");
            }
            return &(node->value);
        }
        const T *operator->() const
        {
            if (node == sentinel || node == nullptr)
            {
                throw std::out_of_range("Cannot dereference");
            }
            return &(node->value);
        }

        BiDirectIterator &operator++()
        {
            if (node == sentinel || node == nullptr)
            {
                throw std::out_of_range("Cannot access element");
            }
            node = node->next;
            return *this;
        }

        BiDirectIterator operator++(int)
        {
            if (node == sentinel || node == nullptr)
            {
                throw std::out_of_range("Cannot access element");
            }
            BiDirectIterator temp = *this;
            node = node->next;
            return temp;
        }

        BiDirectIterator &operator--()
        {
            if (node == nullptr || node->prev == sentinel)
            {
                throw std::out_of_range("Cannot access element");
            }
            node = node->prev;
            return *this;
        }

        BiDirectIterator operator--(int)
        {
            if (node == nullptr || node->prev == sentinel)
            {
                throw std::out_of_range("Cannot access element");
            }
            BiDirectIterator temp = *this;
            node = node->prev;
            return temp;
        }

    private:
        Node *node;
        Node *sentinel;
    };

public:
    void display_forward()
    {
        Node *temp = sentinel_m->next;
        while (temp != sentinel_m)
        {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void display_backward()
    {
        Node *temp = sentinel_m->prev;
        while (temp != sentinel_m)
        {
            std::cout << temp->value << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }

public:
    List() : size_m{0}
    {
        sentinel_m = create_new_sentiel();
    }

    List(size_t count, const T &value) : size_m{count}
    {
        sentinel_m = create_new_sentiel();

        if (count == 0)
        {
            return;
        }

        Node *head = create_new_node(value);
        Node *tail = head;

        for (size_t i = 0; i < count - 1; i++)
        {
            Node *new_node = create_new_node(value);
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }

        sentinel_m->next = head;
        sentinel_m->prev = tail;
        head->prev = sentinel_m;
        tail->next = sentinel_m;
    }

    template <class InputIt>
    List(InputIt first, InputIt last)
    {
        sentinel_m = create_new_sentiel();
        size_m = 0;

        if (first == last)
        {
            sentinel_m->next = sentinel_m;
            sentinel_m->prev = sentinel_m;
            return;
        }

        Node *head = create_new_node(*first++);
        Node *tail = head;
        ++size_m;

        while (first != last)
        {
            Node *new_node = create_new_node(*first++);
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
            ++size_m;
        }

        sentinel_m->next = head;
        sentinel_m->prev = tail;
        head->prev = sentinel_m;
        tail->next = sentinel_m;
    }

    List(const List &other) : size_m{other.size_m}
    {
        sentinel_m = create_new_sentiel();

        if (size_m == 0)
        {
            return;
        }

        Node *current = other.sentinel_m->next;
        Node *head = create_new_node(current->value);
        Node *tail = head;
        current = current->next;

        while (current != other.sentinel_m)
        {
            Node *new_node = create_new_node(current->value);
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
            current = current->next;
        }

        sentinel_m->next = head;
        sentinel_m->prev = tail;
        head->prev = sentinel_m;
        tail->next = sentinel_m;
    }

    List(List &&other) : size_m(other.size_m), sentinel_m(other.sentinel_m)
    {
        other.sentinel_m = create_new_sentiel();
        other.size_m = 0;
    }

    List(std::initializer_list<T> init) : size_m{init.size()}
    {
        sentinel_m = create_new_sentiel();

        if (size_m == 0)
        {
            return;
        }

        auto it = init.begin();
        Node *head = create_new_node(*it++);
        Node *tail = head;

        while (it != init.end())
        {
            Node *new_node = create_new_node(*it++);
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }

        sentinel_m->next = head;
        sentinel_m->prev = tail;
        head->prev = sentinel_m;
        tail->next = sentinel_m;
    }

    ~List()
    {
        clear();
        delete sentinel_m;
    }

    void clear()
    {
        Node *current = sentinel_m->next;
        while (current != sentinel_m)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        sentinel_m->next = sentinel_m;
        sentinel_m->prev = sentinel_m;
        size_m = 0;
    }

    // *iterators

    BiDirectIterator begin()
    {
        return BiDirectIterator(sentinel_m->next, sentinel_m);
    }

    BiDirectIterator end()
    {
        return BiDirectIterator(sentinel_m, sentinel_m);
    }

public:
private:
    Node *sentinel_m;
    std::size_t size_m;
};

#endif