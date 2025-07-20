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
        size_t height;
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
    // # create node
    Node *create_new_node(size_t key, const T &value)
    {
        return new Node{key, value, 1, nullptr, nullptr};
    }

    // # insert node
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

        update_height(node);

        return node;
    }

    // # height functions
    void update_height(Node *node)
    {
        size_t lheight = node->left ? node->left->height : 0;
        size_t rheight = node->right ? node->right->height : 0;
        node->height = std::max(lheight, rheight) + 1;
    }

    // # display
    void display(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }
        display(node->left);
        std::cout << "[ " << node->key << " : " << node->value << " : " << node->height << " ], ";
        display(node->right);
    }

    // # find
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

    // # erase
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

            Node *successor = find_max(node->left);
            node->key = successor->key;
            node->value = successor->value;
            node->left = erase(node->left, successor->key);
        }

        update_height(node);

        return node;
    }

    // # min
    Node *find_min(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // # max
    Node *find_max(Node *node)
    {
        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node;
    }

    // #clear
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