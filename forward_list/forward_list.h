

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <initializer_list>
#include <type_traits>
#include <iterator>
#include <iostream>

template <typename T>
class Forward_list
{

private:
    struct Node
    {
        T value;
        Node *next;
    };

public:
    class forward_iterator
    {
        friend class Forward_list<T>;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        forward_iterator() : node(nullptr) {};
        explicit forward_iterator(Node *n) : node(n) {};
        forward_iterator(const forward_iterator &node) = default;
        forward_iterator &operator=(const forward_iterator &node) = default;

        ~forward_iterator() {}

        bool operator==(const forward_iterator &other) const { return node == other.node; }
        bool operator!=(const forward_iterator &other) const { return node != other.node; }

        T &operator*() { return node->value; }
        const T &operator*() const { return node->value; }

        T *operator->() { return &node->value; }
        const T *operator->() const { return &node->value; }

        forward_iterator &operator++()
        {
            node = node->next;
            return *this;
        }
        forward_iterator operator++(int)
        {
            forward_iterator temp = *this;
            node = node->next;
            return temp;
        }

    private:
        Node *node;
    };

public:
    void display()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Constructors
public:
    Forward_list() : head(nullptr) {};

    Forward_list(size_t count, const T &value) : head(nullptr)
    {
        if (count == 0)
        {
            return;
        }
        fill(count, value);
    }

    template <typename InputIt, typename = std::enable_if_t<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>>
    Forward_list(InputIt first, InputIt last) : head(nullptr)
    {
        if (first == last)
        {
            return;
        }
        copy_values(first, last);
    }

    Forward_list(const Forward_list &other) : head(nullptr)
    {
        if (other.head == nullptr)
        {
            return;
        }
        copy_values(other);
    }

    Forward_list(Forward_list &&other) : head(other.head)
    {
        other.head = nullptr;
    }

    Forward_list(const std::initializer_list<T> &ilist) : head(nullptr)
    {
        if (ilist.size() == 0)
        {
            return;
        }
        copy_values(ilist);
    }

    ~Forward_list()
    {
        clear();
    }

    // assignment operator
public:
    Forward_list &operator=(const Forward_list &other)
    {
        if (this == &other)
        {
            return *this;
        }
        clear();

        if (other.head == nullptr)
        {
            return *this;
        }
        copy_values(other);

        return *this;
    }

    Forward_list &operator=(Forward_list &&other)
    {
        if (this == &other)
        {
            return *this;
        }
        clear();

        head = other.head;
        other.head = nullptr;
        return *this;
    }

    // assign
public:
    void assign(size_t count, const T &value)
    {
        clear();
        if (count == 0)
        {
            return;
        }
        fill(count, value);
    }

    template <typename InputIt, typename = std::enable_if_t<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>>
    void assign(InputIt first, InputIt last)
    {
        clear();
        if (first == last)
        {
            return;
        }
        copy_values(first, last);
    }

    void assign(std::initializer_list<T> ilist)
    {
        clear();
        if (ilist.size() == 0)
        {
            return;
        }
        copy_values(ilist);
    }

    // Element access
public:
    T &front()
    {
        return head->value;
    }

    const T &front() const
    {
        return head->value;
    }

    // Capacity
public:
    bool empty() const noexcept
    {
        return head == nullptr;
    }

    forward_iterator insert_after(forward_iterator pos, const T &value)
    {
        if (pos.node == nullptr)
        {
            throw std::invalid_argument("Cannot insert after end()");
        }

        Node *new_node = create_new_node(value);
        Node *next = pos.node->next;
        pos.node->next = new_node;
        new_node->next = next;
        return forward_iterator(new_node);
    }

    forward_iterator insert_after(forward_iterator pos, T &&value)
    {
        if (pos.node == nullptr)
        {
            throw std::invalid_argument("Cannot insert after end()");
        }
        Node *new_node = create_new_node(std::move(value));
        Node *next = pos.node->next;
        pos.node->next = new_node;
        new_node->next = next;
        return forward_iterator(new_node);
    }

    forward_iterator insert_after(forward_iterator pos, size_t count, const T &value)
    {
        if (count == 0)
        {
            return pos;
        }
        if (pos.node == nullptr)
        {
            throw std::invalid_argument("Cannot insert after end()");
        }

        Node *temp_head = create_new_node(value);
        Node *temp_tail = temp_head;

        for (size_t i = 0; i < count - 1; i++)
        {
            Node *new_node = create_new_node(value);
            temp_tail->next = new_node;
            temp_tail = new_node;
        }

        Node *next = pos.node->next;
        pos.node->next = temp_head;
        temp_tail->next = next;

        return forward_iterator(temp_tail);
    }

    template <typename InputIt, typename = std::enable_if_t<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>>
    forward_iterator insert_after(forward_iterator pos, InputIt first, InputIt last)
    {
        if (first == last)
        {
            return pos;
        }

        if (pos.node == nullptr)
        {
            throw std::invalid_argument("Cannot insert after end()");
        }

        Node *temp_head = create_new_node(*first++);
        Node *temp_tail = temp_head;

        while (first != last)
        {
            Node *new_node = create_new_node(*first++);
            temp_tail->next = new_node;
            temp_tail = new_node;
        }

        Node *next = pos.node->next;
        pos.node->next = temp_head;
        temp_tail->next = next;

        return forward_iterator(temp_tail);
    }

    forward_iterator insert_after(forward_iterator pos, std::initializer_list<T> ilist)
    {
        if (ilist.size() == 0)
        {
            return pos;
        }

        if (pos.node == nullptr)
        {
            throw std::invalid_argument("Cannot insert after end()");
        }

        auto it = ilist.begin();

        Node *temp_head = create_new_node(*it++);
        Node *temp_tail = temp_head;

        while (it != ilist.end())
        {
            Node *new_node = create_new_node(*it++);
            temp_tail->next = new_node;
            temp_tail = new_node;
        }

        Node *next = pos.node->next;
        pos.node->next = temp_head;
        temp_tail->next = next;

        return forward_iterator(temp_tail);
    }

    template <class... Args>
    forward_iterator emplace_after(forward_iterator pos, Args &&...args)
    {
        if (pos.node == nullptr)
        {
            throw std::invalid_argument("Cannot insert after end()");
        }

        Node *new_node = new Node(std::forward<Args>(args)...);
        Node *next = pos.node->next;
        pos.node->next = new_node;
        new_node->next = next;

        return forward_iterator(new_node);
    }

    forward_iterator erase_after(forward_iterator pos)
    {
        if (pos.node == nullptr)
        {
            throw std::invalid_argument("Cannot erase after end()");
        }
        if (pos.node->next == nullptr)
        {
            return forward_iterator(nullptr);
        }

        if (pos.node->next == head)
        {
            pop_front();
            return forward_iterator(head);
        }

        Node *erase_element = pos.node->next;
        Node *next_after_erased = erase_element->next;
        delete erase_element;
        pos.node->next = next_after_erased;
        return forward_iterator(next_after_erased);
    }

    forward_iterator erase_after(forward_iterator first, forward_iterator last)
    {
        if (first == last)
        {
            return last;
        }
        if (first.node == nullptr)
        {
            throw std::invalid_argument("Cannot erase after end()");
        }

        Node *current = first.node->next;
        while (current != last.node)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        first.node->next = last.node;
        return last;
    }

    void push_front(const T &value)
    {
        Node *new_head = create_new_node(value);
        new_head->next = head;
        head = new_head;
    }

    void push_front(T &&value)
    {
        Node *new_head = create_new_node(std::move(value));
        new_head->next = head;
        head = new_head;
    }

    template <class... Args>
    T &emplace_front(Args &&...args)
    {
        Node *new_head = new Node(std::forward<Args>(args)...);
        new_head->next = head;
        head = new_head;
        return head->value;
    }

    void pop_front()
    {
        if (empty())
        {
            return;
        }
        Node *next = head->next;
        delete head;
        head = next;
    }

    void resize(size_t count, const T &value = T())
    {

        if (count == 0)
        {
            clear();
            return;
        }

        if (!head)
        {
            head = create_new_node(value);
            insert_after(forward_iterator(head), count - 1, value);
            return;
        }

        size_t i = 1;
        Node *current = head;

        while (current->next != nullptr && i < count)
        {
            current = current->next;
            i++;
        }
        if (current->next != nullptr)
        {
            erase_after(forward_iterator(current), end());
        }
        else
        {
            insert_after(forward_iterator(current), count - i, value);
        }
    }

    void swap(Forward_list &other)
    {
        Node *temp = other.head;
        other.head = head;
        head = temp;
    }

    void remove(const T &value)
    {
        if (head == nullptr)
        {
            return;
        }

        while (head != nullptr && head->value == value)
        {
            pop_front();
        }

        Node *current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (current->next->value == value)
            {
                erase_after(forward_iterator(current));
            }
            else
            {
                current = current->next;
            }
        }
    }

    template <class UnaryPred>
    void remove_if(UnaryPred p)
    {
        if (head == nullptr)
        {
            return;
        }
        while (head != nullptr && p(head->value))
        {
            pop_front();
        }

        Node *current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (p(current->next->value))
            {
                erase_after(forward_iterator(current));
            }
            else
            {
                current = current->next;
            }
        }
    }

    void unique()
    {
        if (head == nullptr)
        {
            return;
        }
        Node *current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (current->value == current->next->value)
            {
                erase_after(forward_iterator(current));
            }
            else
            {
                current = current->next;
            }
        }
    }

    template <class BinaryPred>
    void unique(BinaryPred p)
    {
        if (head == nullptr)
        {
            return;
        }
        Node *current = head;

        while (current != nullptr && current->next != nullptr)
        {
            if (p(current->value, current->next->value))
            {
                erase_after(forward_iterator(current));
            }
            else
            {
                current = current->next;
            }
        }
    }

    void reverse() noexcept
    {
        if (head == nullptr)
        {
            return;
        }

        Node *new_head = nullptr;

        while (head != nullptr)
        {
            Node *next = head->next;
            head->next = new_head;
            new_head = head;
            head = next;
        }
        head = new_head;
    }

    // Iterators
public:
    forward_iterator begin() noexcept
    {
        return forward_iterator(head);
    }

    forward_iterator end() noexcept
    {
        return forward_iterator(nullptr);
    }

    // Modifiers
public:
    void clear() noexcept
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

private:
    Node *create_new_node(const T &value)
    {
        return new Node{value, nullptr};
    }

    Node *create_new_node(T &&value)
    {
        return new Node{std::move(value)};
    }

    void fill(size_t count, const T &value)
    {
        for (size_t i = 0; i < count; i++)
        {
            Node *new_head = create_new_node(value);
            new_head->next = head;
            head = new_head;
        }
    }

    void copy_values(const Forward_list &other)
    {

        Node *temp = other.head;

        // create head
        head = create_new_node(temp->value);
        Node *tail = head;
        temp = temp->next;

        while (temp != nullptr)
        {
            Node *new_tail = create_new_node(temp->value);
            tail->next = new_tail;
            tail = new_tail;
            temp = temp->next;
        }
    }

    template <typename InputIt, typename = std::enable_if_t<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>>
    void copy_values(InputIt first, InputIt last)
    {
        head = create_new_node(*first++);
        Node *tail = head;
        while (first != last)
        {
            Node *new_tail = create_new_node(*first++);
            tail->next = new_tail;
            tail = new_tail;
        }
    }

    void copy_values(const std::initializer_list<T> &ilist)
    {
        auto it = ilist.begin();

        head = create_new_node(*it++);
        Node *tail = head;

        while (it != ilist.end())
        {
            Node *new_tail = create_new_node(*it++);
            tail->next = new_tail;
            tail = new_tail;
        }
    }

public:
    Node *head;
};

#endif
