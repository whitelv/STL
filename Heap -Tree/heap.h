#ifndef HEAP_H
#define HEAP_H

#include <list>
#include <iostream>


template <typename T>
class Heap
{
public:
    struct Node
    {
        T value;
        Node *parent;
        Node *left;
        Node *right;
    };

    // # Constructor & Destructor
public:
    Heap() : root{nullptr} {}
    ~Heap() { clear(); }

    // # Modifiers
public:
    void insert(const T &value)
    {
        auto inserted_node = insert_node(value);
        heapify_up(inserted_node);
    }

    void remove_min()
    {
        erase(0);
    }

    void erase(size_t index)
    {
        if (root == nullptr)
        {
            throw std::out_of_range("Error: Index must be in less than size");
        }

        auto node = find_node(index);
        auto last_item = nodes.back();

        if (last_item == root)
        {
            delete root;
            root = nullptr;
            nodes.clear();
            return;
        }

        auto l_parent = last_item->parent;
        std::swap(node->value, last_item->value);

        if (l_parent->left == last_item)
        {
            l_parent->left = nullptr;
        }
        else
        {
            l_parent->right = nullptr;
        }

        nodes.pop_back();
        if (nodes.front() != l_parent)
        {
            nodes.push_front(l_parent);
        }
        delete last_item;
        heapify_down(node);
    }

    void change_value(size_t index, const T &new_value)
    {
        auto node = find_node(index);
        auto prev_value = node->value;

        if (prev_value == new_value)
        {
            return;
        }

        node->value = new_value;

        if (prev_value > new_value)
        {
            heapify_up(node);
            return;
        }
        heapify_down(node);
    }

    void clear()
    {
        BFS([](Node *node)
            { delete node; });
        root = nullptr;
        nodes.clear();
    }

    // # Observers
public:
    const T *get_min() const
    {
        return root == nullptr ? nullptr : &root->value;
    }

    void display()
    {
        BFS([](Node *node)
            { std::cout << "[ " << node->value << " ], " << std::flush; });
    }

    // # Helper functions
private:
    Node *create_new_node(const T &value, Node *parent) const
    {
        return new Node{value, parent, nullptr, nullptr};
    }

    Node *insert_node(const T &value)
    {
        if (root == nullptr)
        {
            root = create_new_node(value, nullptr);
            nodes.push_back(root);
            return root;
        }
        auto front = nodes.front();

        if (front->left && front->right)
        {
            nodes.pop_front();
            front = nodes.front();
        }

        if (front->left == nullptr)
        {
            front->left = create_new_node(value, front);
            nodes.push_back(front->left);
            return front->left;
        }

        front->right = create_new_node(value, front);
        nodes.push_back(front->right);
        return front->right;
    }

    void heapify_up(Node *node)
    {
        if (node->parent == nullptr)
        {
            return;
        }
        auto parent = node->parent;

        if (parent->value > node->value)
        {
            std::swap(parent->value, node->value);
            heapify_up(parent);
        }
    }

    void heapify_down(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (!node->left && !node->right)
        {
            return;
        }
        auto l_child = node->left;
        auto r_child = node->right;

        if (l_child && r_child)
        {
            if (l_child->value < r_child->value && l_child->value < node->value)
            {
                std::swap(l_child->value, node->value);
                heapify_down(l_child);
                return;
            }

            if (r_child->value < l_child->value && r_child->value < node->value)
            {
                std::swap(r_child->value, node->value);
                heapify_down(r_child);
                return;
            }
            return;
        }
        if (l_child && l_child->value < node->value)
        {
            std::swap(l_child->value, node->value);
            heapify_down(l_child);
            return;
        }
        if (r_child && r_child->value < node->value)
        {
            std::swap(r_child->value, node->value);
            heapify_down(r_child);
            return;
        }
    }

    std::string number_to_bits(size_t number) const
    {
        auto bit = std::bitset<sizeof(size_t) * 8>{number}.to_string();
        bit.erase(bit.begin(), bit.begin() + bit.find("1") + 1);
        return bit;
    }

    Node *find_node(size_t index)
    {
        if (root == nullptr)
        {
            throw std::out_of_range("Error: Index must be in less than size");
        }

        auto bits = number_to_bits(index + 1);
        auto current = root;
        for (size_t i = 0; i < bits.size(); i++)
        {
            if (bits[i] == '0')
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }

            if (current == nullptr)
            {
                throw std::out_of_range("Error: Index must be in less than size");
            }
        }
        return current;
    }

    void BFS(std::function<void(Node *)> func)
    {
        if (root == nullptr)
            return;

        std::queue<Node *> visited;
        visited.push(root);
        while (!visited.empty())
        {
            Node *front = visited.front();
            func(front);
            if (front->left != nullptr)
            {
                visited.push(front->left);
            }
            if (front->right != nullptr)
            {
                visited.push(front->right);
            }
            visited.pop();
        }
    }

private:
    Node *root;
    std::list<Node *> nodes;
};

#endif