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

    using EdgeNodes = std::pair<Node *, Node *>;

public:
    class BiDirectIterator
    {
        friend class List;
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

    // * display
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

    // * Constructors
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

        auto [head, tail] = create_range(count, value);

        sentinel_m->next = head;
        sentinel_m->prev = tail;
        head->prev = sentinel_m;
        tail->next = sentinel_m;
    }

    template <typename InputIt>
    List(InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value>::type * = nullptr)
    {
        sentinel_m = create_new_sentiel();
        size_m = 0;

        if (first == last)
        {
            sentinel_m->next = sentinel_m;
            sentinel_m->prev = sentinel_m;
            return;
        }

        auto [head, tail] = create_range(first, last);

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

        copy_from_List(other);
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

        auto [head, tail] = create_range(init);

        sentinel_m->next = head;
        sentinel_m->prev = tail;
        head->prev = sentinel_m;
        tail->next = sentinel_m;
    }

    // * Destructor
    ~List()
    {
        clear();
        delete sentinel_m;
    }

    // * operator=
    List &operator=(const List &other)
    {
        if (this == &other)
        {
            return *this;
        }
        clear();
        delete sentinel_m;

        size_m = other.size_m;
        sentinel_m = create_new_sentiel();

        if (size_m == 0)
        {
            return *this;
        }

        copy_from_List(other);

        return *this;
    }

    List &operator=(List &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        clear();
        delete sentinel_m;

        size_m = other.size_m;
        sentinel_m = other.sentinel_m;

        other.size_m = 0;
        other.sentinel_m = create_new_sentiel();

        return *this;
    }

    // * Element access
public:
    T &front()
    {
        if (sentinel_m->next == sentinel_m)
        {
            throw std::out_of_range("Cannot derefence value");
        }
        return sentinel_m->next->value;
    }

    T &back()
    {
        if (sentinel_m->prev == sentinel_m)
        {
            throw std::out_of_range("Cannot derefence value");
        }
        return sentinel_m->prev->value;
    }

    // *iterators
public:
    BiDirectIterator begin()
    {
        return BiDirectIterator(sentinel_m->next, sentinel_m);
    }

    BiDirectIterator end()
    {
        return BiDirectIterator(sentinel_m, sentinel_m);
    }

    // * Capacity
public:
    bool empty() const noexcept
    {
        return size_m == 0;
    }

    size_t size() const
    {
        return size_m;
    }

    // * Modifiers
public:
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

    // * Insert
    BiDirectIterator insert(BiDirectIterator pos, const T &value)
    {
        if (pos.node == nullptr)
        {
            return pos;
        }

        Node *new_node = create_new_node(value);
        link_nodes(pos.node->prev, new_node, new_node, pos.node);
        ++size_m;

        return BiDirectIterator(new_node, sentinel_m);
    }

    BiDirectIterator insert(BiDirectIterator pos, size_t count, const T &value)
    {
        if (count == 0 || pos.node == nullptr)
        {
            return pos;
        }

        auto [head, tail] = create_range(count, value);
        link_nodes(pos.node->prev, head, tail, pos.node);
        size_m += count;

        return BiDirectIterator(head, sentinel_m);
    }

    template <class InputIt>
    BiDirectIterator insert(BiDirectIterator pos, InputIt first, InputIt last,
                            typename std::enable_if<!std::is_integral<InputIt>::value>::type * = nullptr)
    {
        if (first == last || pos.node == nullptr)
        {
            return pos;
        }

        auto [head, tail] = create_range(first, last);
        link_nodes(pos.node->prev, head, tail, pos.node);

        return BiDirectIterator(head, sentinel_m);
    }

    BiDirectIterator insert(BiDirectIterator pos, std::initializer_list<T> ilist)
    {
        if (ilist.size() == 0 || pos.node == nullptr)
        {
            return pos;
        }

        auto [head, tail] = create_range(ilist);
        link_nodes(pos.node->prev, head, tail, pos.node);
        size_m += ilist.size();

        return BiDirectIterator(head, sentinel_m);
    }

    // * erase
    BiDirectIterator erase(BiDirectIterator pos)
    {
        if (pos.node == nullptr || pos == end())
        {
            throw std::invalid_argument("invalid pos");
        }
        Node *prev = pos.node->prev;
        Node *next = pos.node->next;

        prev->next = next;
        next->prev = prev;
        delete pos.node;

        --size_m;

        return BiDirectIterator(next, sentinel_m);
    }

    BiDirectIterator erase(BiDirectIterator first, BiDirectIterator last)
    {
        if (first == last)
        {
            return last;
        }

        Node *prev = first.node->prev;
        Node *stop = last.node;

        Node *current = first.node;
        while (current != stop)
        {
            Node *next = current->next;
            delete current;
            current = next;
            --size_m;
        }

        prev->next = stop;
        stop->prev = prev;

        return BiDirectIterator(stop, sentinel_m);
    }

    // * back methods
    void push_back(const T &value)
    {
        Node *prev = sentinel_m->prev;
        Node *new_node = create_new_node(value);

        prev->next = new_node;
        new_node->prev = prev;

        sentinel_m->prev = new_node;
        new_node->next = sentinel_m;

        ++size_m;
    }

    void pop_back()
    {
        if (empty())
        {
            return;
        }

        Node *tail = sentinel_m->prev;
        Node *prev = tail->prev;

        delete tail;

        prev->next = sentinel_m;
        sentinel_m->prev = prev;

        --size_m;
    }

    // * front methods

    void push_front(const T &value)
    {
        Node *next = sentinel_m->next;
        Node *new_node = create_new_node(value);

        next->prev = new_node;
        new_node->next = next;

        sentinel_m->next = new_node;
        new_node->prev = sentinel_m;

        ++size_m;
    }

    void pop_front()
    {
        if (empty())
        {
            return;
        }

        Node *head = sentinel_m->next;
        Node *next = head->next;

        delete head;

        sentinel_m->next = next;
        next->prev = sentinel_m;

        --size_m;
    }

private:
    void copy_from_List(const List &other)
    {
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

    EdgeNodes create_range(size_t count, const T &value)
    {
        Node *head = create_new_node(value);
        Node *tail = head;

        for (size_t i = 0; i < count - 1; i++)
        {
            Node *new_node = create_new_node(value);
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }

        return {head, tail};
    }

    template <typename InputIt>
    EdgeNodes create_range(InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value>::type * = nullptr)
    {
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
        return {head, tail};
    }

    EdgeNodes create_range(std::initializer_list<T> init)
    {
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
        return {head, tail};
    }

    void link_nodes(Node *before, Node *head, Node *tail, Node *after)
    {
        before->next = head;
        head->prev = before;

        tail->next = after;
        after->prev = tail;
    }

private:
    Node *sentinel_m;
    std::size_t size_m;
};

#endif