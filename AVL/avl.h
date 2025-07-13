#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iostream>
#include <queue>

template <typename U, typename T>
class AVL
{
private:
    struct Node
    {
        U key;
        T value;
        size_t height;
        Node *left;
        Node *right;
    };

public:
    // ** Constructor & Destructor
    AVL() : root{nullptr} {}
    ~AVL() { clear(root); }

    // ** Modifiers
public:
    void insert(const U &key, const T &value)
    {
        root = insert(key, value, root);
    }

    void erase(const U &key)
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
    // * display functions
    void display() const
    {
        display(root);
    }

    void BFS()
    {
        if (root == nullptr)
            return;

        std::queue<Node *> visited;
        visited.push(root);
        while (!visited.empty())
        {
            Node *front = visited.front();
            std::cout << "[ " << front->key << " : " << front->value << " : " << front->height << " ], ";
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

    // * find
    T *find(U key)
    {
        Node *found_node = find(root, key);
        return found_node == nullptr ? nullptr : &found_node->value;
    }

    // * height
    size_t tree_height()
    {
        return get_height(root);
    }

    // * min

    T * min(){
        return root ? &find_min(root)->value : nullptr;
    }

    T * max(){
        return root ? &find_max(root)->value : nullptr;
    }

    
    // ** Helper functions
private:
    // # create node
    Node *create_new_node(const U &key, const T &value)
    {
        return new Node{key, value, 1, nullptr, nullptr};
    }

    // # display
    void display(Node *node) const
    {
        if (node == nullptr)
        {
            return;
        }
        display(node->left);
        std::cout << "[ " << node->key << " : " << node->value << " : " << node->height <<  " ], ";
        display(node->right);
    }

    // # insert
    Node *insert(const U &key, const T &value, Node *node)
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

        return rebalance(node);
    }

    // # height functions
    size_t get_height(Node *node) const
    {
        return node ? node->height : 0;
    }

    void update_height(Node *node)
    {
        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
    }

    int balance_factor(Node *node)
    {
        return get_height(node->left) - get_height(node->right);
    }

    // # rotations
    Node *left_rotation(Node *node)
    {
        Node *child = node->right;
        node->right = child->left;
        child->left = node;

        update_height(node);
        update_height(child);

        return child;
    }

    Node *right_rotation(Node *node)
    {
        Node *child = node->left;
        node->left = child->right;
        child->right = node;

        update_height(node);
        update_height(child);

        return child;
    }

    Node *left_right_rotation(Node *node)
    {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }

    Node *right_left_rotation(Node *node)
    {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

    // # rebalance
    Node *rebalance(Node *node)
    {
        int node_bf = balance_factor(node);

        if (node_bf < -1)
        {
            int right_child_bf = balance_factor(node->right);
            if (right_child_bf > 0)
            {
                return right_left_rotation(node);
            }
            return left_rotation(node);
        }

        if (node_bf > 1)
        {
            int left_child_bf = balance_factor(node->left);
            if (left_child_bf < 0)
            {
                return left_right_rotation(node);
            }
            return right_rotation(node);
        }

        return node;
    }

    // # find
    Node *find(Node *node, const U &key)
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

    // #erase
    Node *erase(Node *node, const U &key)
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

        return rebalance(node);
    }

    // # find_min
    Node *find_min(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // # find_max
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