#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iostream>

template <typename T>
class BST
{
private:
    struct Node
    {
        size_t key;
        T value;
        Node *left;
        Node *right;
    };

public:
    // ** Constructor & Destructor
    BST() : root{nullptr} {}
    ~BST() { clear(root); }

    // ** Modifiers
public:
    void insert(size_t key, const T &value)
    {
        root = insert(key, value, root);
    }

    void erase(size_t key)
    {
        root = erase(root, key);
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    // ** Observers
public:
    void display() const
    {
        display(root);
    }

    T *find(size_t key)
    {
        Node *found_node = find(root, key);
        return found_node == nullptr ? nullptr : &found_node->value;
    }

    // ** Helper functions
private:
    Node *create_new_node(size_t key, const T &value)
    {
        return new Node{key, value, nullptr, nullptr};
    }

    Node *insert(size_t key, const T &value, Node *node)
    {
        if (node == nullptr)
        {
            node = create_new_node(key, value);
            return node;
        }

        if (key < node->key)
        {
            node->left = insert(key, value, node->left);
        }
        else if (key > node->key)
        {
            node->right = insert(key, value, node->right);
        }
        return node;
    }

    void display(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }
        display(node->left);
        std::cout << "[ " << node->key << " : " << node->value << " ], ";
        display(node->right);
    }

    Node *find(Node *node, size_t key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (key < node->key)
        {
            node = find(node->left, key);
        }
        else if (key > node->key)
        {
            node = find(node->left, key);
        }
        return node;
    }

    Node *erase(Node *node, size_t key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (key < node->key)
        {
            node->left = erase(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = erase(node->right, key);
        }
        else
            (key == node->key)
            {
                if (node->left == nullptr && node->right == nullptr)
                {
                    delete node;
                    return nullptr;
                }
                else if (node->left != nullptr && node->right == nullptr)
                {
                    Node *new_left = node->left;
                    delete node;
                    return new_left;
                }
                else if (node->right != nullptr && node->left == nullptr)
                {
                    Node *new_right = node->right;
                    delete node;
                    return new_right;
                }
                else
                {
                    Node *successor = find_min(node->right);
                    size_t temp_key = successor->key;
                    T temp_value = successor->value;
                    successor->key = node->key;
                    successor->value = node->value;
                    node->key = temp_key;
                    node->value = temp_value;
                    node->right = erase(node->right, key);
                }
            }
        return node;
    }

    Node *find_min(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    void clear(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

private:
    Node *root;
};

#endif