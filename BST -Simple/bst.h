#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iostream>
#include <queue>

template <typename T>
class BST
{
public:
    struct Node
    {
        size_t key;
        T value;
        Node *left;
        Node *right;
    };

    // ** Modifiers
public:
    // * insert
    void insert(size_t key, const T &value)
    {
        if (root == nullptr)
        {
            root = create_new_node(key, value);
            return;
        }
        Node *parent = root;
        while (true)
        {
            if (key < parent->key && parent->left == nullptr)
            {
                parent->left = create_new_node(key, value);
                return;
            }
            else if (key > parent->key && parent->right == nullptr)
            {
                parent->right = create_new_node(key, value);
                return;
            }
            else if (key > parent->key && parent->right != nullptr)
            {
                parent = parent->right;
            }
            else if (key < parent->key && parent->left != nullptr)
            {
                parent = parent->left;
            }
        }
    }

    // * erase
    void erase(size_t key)
    {
        if (root == nullptr)
        {
            return;
        }
        if (root->key == key)
        {
            root = erase_node(root);
            return;
        }

        Node *target_parent = find_parent(root, key);
        if (!target_parent)
        {
            return;
        }

        if (target_parent->left->key == key)
        {
            Node *target = target_parent->left;
            target_parent->left = erase_node(target);
        }
        else if (target_parent->right->key == key)
        {
            Node *target = target_parent->right;
            target_parent->right = erase_node(target);
        }
    }

    // * clear
    void clear()
    {
        DFS([](Node *node)
            { delete node; });
        root = nullptr;
    }

    // ** Observers
public:
    // * display
    void display()
    {
        DFS([](Node *node)
            { std::cout << "[ " << node->key << " : " << node->value << " ], " << std::flush; });
    }

    // * find
    T *find(size_t key) const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        Node *target = root;
        while (target != nullptr)
        {
            if (key < target->key)
            {
                target = target->left;
            }
            else if (key > target->key)
            {
                target = target->right;
            }
            else
            {
                return &target->value;
            }
        }
        return nullptr;
    }

    // ** Constructor && Destuctor
public:
    BST() : root{nullptr} {}
    ~BST()
    {
        DFS([](Node *node)
            { delete node; });
    }

    // ** Helper Functions
private:
    Node *create_new_node(size_t key, const T &value)
    {
        return new Node{key, value, nullptr, nullptr};
    }

    // * find parent
    Node *find_parent(Node *node, size_t key)
    {
        Node *target_parent = root;
        bool target_found = false;

        while (!target_found)
        {
            if (key < target_parent->key)
            {
                if (target_parent->left == nullptr)
                {
                    break;
                }
                else if (target_parent->left->key == key)
                {
                    target_found = true;
                }
                else
                {
                    target_parent = target_parent->left;
                }
            }
            else if (key > target_parent->key)
            {
                if (target_parent->right == nullptr)
                {
                    break;
                }
                else if (target_parent->right->key == key)
                {
                    target_found = true;
                }
                else
                {
                    target_parent = target_parent->right;
                }
            }
        }
        return target_found ? target_parent : nullptr;
    }

    // * erase node
    Node *erase_node(Node *target)
    {

        if (target->left == nullptr && target->right == nullptr)
        {
            delete target;
            return nullptr;
        }
        else if (target->left != nullptr && target->right == nullptr)
        {
            Node *new_target = target->left;
            delete target;
            return new_target;
        }
        else if (target->right != nullptr && target->left == nullptr)
        {
            Node *new_target = target->right;
            delete target;
            return new_target;
        }
        else
        {
            Node *successor = find_min(target->right);
            Node *successor_parent = find_parent(target, successor->key);

            if (successor_parent->left == successor)
                successor_parent->left = nullptr;
            else
                successor_parent->right = nullptr;

            successor->left = target->left;
            successor->right = target->right;
            delete target;
            return successor;
        }
    }

    // * DFS
    void DFS(void (*func)(Node *))
    {
        if (root == nullptr)
            return;

        std::queue<Node *> visited;
        visited.push(root);
        while (!visited.empty())
        {
            func(visited.front());
            if (visited.front()->left != nullptr)
            {
                visited.push(visited.front()->left);
            }
            if (visited.front()->right != nullptr)
            {
                visited.push(visited.front()->right);
            }
            visited.pop();
        }
    }

    // * find min
    Node *find_min(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

public:
    Node *root;
};

#endif