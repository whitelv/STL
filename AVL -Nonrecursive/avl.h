#ifndef AVL_H
#define AVL_H

#include <cstddef>
#include <iostream>
#include <queue>
#include <stack>
#include <functional>

template <typename U, typename T>
class AVL
{

public:
    struct Node
    {
        U key;
        T value;
        size_t height;
        Node *left;
        Node *right;
    };

    // ** Observers
public:
    // * display
    void display()
    {
        BFS([](Node *node)
            { std::cout << "[ " << node->key << " : " << node->height << " ], " << std::flush; });
    }

    // ** Modifiers
public:
    // # insert
    void insert(const U &key, const T &value)
    {
        if (root == nullptr)
        {
            root = create_new_node(key, value);
            return;
        }

        std::stack<Node *> traversed_nodes;

        Node *parent = root;
        while (true)
        {
            traversed_nodes.push(parent);
            if (key < parent->key && parent->left == nullptr)
            {
                parent->left = create_new_node(key, value);
                break;
            }
            else if (key > parent->key && parent->right == nullptr)
            {
                parent->right = create_new_node(key, value);
                break;
            }
            else if (key > parent->key && parent->right != nullptr)
            {
                parent = parent->right;
            }
            else if (key < parent->key && parent->left != nullptr)
            {
                parent = parent->left;
            }
            else
            {
                throw std::invalid_argument("ERROR: KEY MUST BE UNIQUE");
            }
        }
        root = fix_tree(traversed_nodes);
    }

    // # erase
    void erase(const U &key)
    {
        if (root == nullptr)
        {
            return;
        }
        std::stack<Node *> traversed_nodes;

        // ** traverse tree and find node
        find_way(key, root, traversed_nodes);
        Node *target_node = traversed_nodes.top();

        // ** check if last traversed node's key == key
        if (target_node->key != key)
        {
            return;
        }
        traversed_nodes.pop();

        // ** check if trget node is root
        if (traversed_nodes.empty())
        {
            root = erase_node(target_node);
            return;
        }

        // ** get parent of node
        Node *parent = traversed_nodes.top();

        if (parent->left == target_node)
        {
            parent->left = erase_node(target_node);
        }
        else
        {
            parent->right = erase_node(target_node);
        }

        root = fix_tree(traversed_nodes);
    }

    // ** Helper Functions
private:
    void find_way(const U &key, Node *current, std::stack<Node *> &traversed_nodes)
    {
        while (current != nullptr)
        {
            traversed_nodes.push(current);
            if (key < current->key)
            {
                current = current->left;
                continue;
            }
            if (key > current->key)
            {
                current = current->right;
                continue;
            }
            break;
        }
    }



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
        Node *successor = find_max(target->left);
        std::stack<Node *> traversed_nodes;
        find_way(successor->key, target, traversed_nodes);
        traversed_nodes.pop();

        target->key = successor->key;
        target->value = successor->value;

        Node *parent = traversed_nodes.top();
        if (parent->left == successor)
        {
            parent->left = erase_node(successor);
        }
        else
        {
            parent->right = erase_node(successor);
        }

        return fix_tree(traversed_nodes);
    }


    // # \fix tree
    Node *fix_tree(std::stack<Node *> &traversed_nodes)
    {
        Node *current;
        Node *parent;

        while (!traversed_nodes.empty())
        {
            current = traversed_nodes.top();
            traversed_nodes.pop();
            update_height(current);

            if (traversed_nodes.empty())
            {
                return rebalance(current);
            }

            parent = traversed_nodes.top();

            if (parent->left == current)
            {
                parent->left = rebalance(current);
                continue;
            }
            parent->right = rebalance(current);
        }

        return current;
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

    // # height functions
    size_t get_height(Node *node)
    {
        return node ? node->height : 0;
    }

    void update_height(Node *node)
    {
        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
    }

    size_t balance_factor(Node *node)
    {
        return get_height(node->left) - get_height(node->right);
    }

    // #create new node
    Node *create_new_node(const U &key, const T &value)
    {
        return new Node{key, value, 1, nullptr, nullptr};
    }

    // #BFS
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

    // #min()
    Node *find_min(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // #max()
    Node *find_max(Node *node)
    {
        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node;
    }

    // ** Constructor && Destuctor
public:
    AVL() : root{nullptr} {}
    ~AVL()
    {
        BFS([](Node *node)
            { delete node; });
    }

private:
    Node *root;
};

#endif