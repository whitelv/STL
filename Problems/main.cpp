
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stack>
#include <unordered_map>

std::vector<char> generate_perfect_tree(size_t number)
{
    size_t nodes_counter = std::pow(2, number * 2) - 1;
    std::vector<char> complete_tree(nodes_counter, '(');

    for (size_t i = 2; i < nodes_counter; i += 2)
    {
        complete_tree[i] = ')';
    }
    return complete_tree;
}

long left_child(size_t parent, size_t size)
{
    size_t left_child = 2 * parent + 1;
    return left_child < size ? left_child : -1;
}

long right_child(size_t parent, size_t size)
{
    size_t right_child = 2 * parent + 2;
    return right_child < size ? right_child : -1;
}

std::vector<std::string> generateParenthesis(size_t number)
{
    std::vector<char> tree = generate_perfect_tree(number);
    std::vector<std::string> result;
    std::unordered_map<size_t, bool> visited;
    std::string current;
    std::stack<size_t> stack;
    size_t left_parenthesis_counter = 0;
    size_t right_parenthesis_counter = 0;

    stack.push(0);

    while (!stack.empty())
    {
        size_t top = stack.top();

        if (visited.count(top))
        {
            stack.pop();
            current.pop_back();
            left_parenthesis_counter -= tree[top] == '(' ? 1 : 0;
            right_parenthesis_counter -= tree[top] == ')' ? 1 : 0;
            continue;
        }

        current += tree[top];
        left_parenthesis_counter += tree[top] == '(' ? 1 : 0;
        right_parenthesis_counter += tree[top] == ')' ? 1 : 0;

        if (left_child(top, tree.size()) == -1 && right_child(top, tree.size()) == -1)
        {
            stack.pop();
            result.push_back(current);
            current.pop_back();
            left_parenthesis_counter -= tree[top] == '(' ? 1 : 0;
            right_parenthesis_counter -= tree[top] == ')' ? 1 : 0;
            continue;
        }

        if (left_parenthesis_counter > right_parenthesis_counter && right_parenthesis_counter < number)
        {
            stack.push(right_child(top, tree.size()));
        }
        if (left_parenthesis_counter < number)
        {
            stack.push(left_child(top, tree.size()));
        }

        visited[top] = true;
    }

    return result;
}

int main()
{
    std::vector<std::string> result = generateParenthesis(3);
    std::cout << left_child(0, 3);
}