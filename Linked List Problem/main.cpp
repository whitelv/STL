#include <stdexcept>
#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *removeNthFromEnd(ListNode *head, int n)
{
    if (head == nullptr)
    {
        throw std::invalid_argument("Error: head is nullptr");
    }

    if (n < 0)
    {
        throw std::invalid_argument("Error: n must be positive");
    }

    if (n == 0)
    {
        return head;
    }
    ListNode *fake_head = new ListNode(0, head);
    ListNode *first_ptr = fake_head;
    ListNode *second_ptr = fake_head;

    int first_counter = 0;
    int second_counter = 0;

    while (first_ptr != nullptr)
    {
        first_ptr = first_ptr->next;
        first_counter++;
        if (first_counter - second_counter > n + 1)
        {
            second_ptr = second_ptr->next;
            second_counter++;
        }
    }

    if (first_counter - second_counter != n + 1)
    {
        delete fake_head;
        return head;
    }

    ListNode *next = second_ptr->next->next;
    delete second_ptr->next;
    second_ptr->next = next;

    head = fake_head->next;
    delete fake_head;

    return head;
}

ListNode *insertNode(ListNode *head, int n)
{
    if (head == nullptr)
    {
        return new ListNode(n);
    }
    ListNode *tail = head;

    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    tail->next = new ListNode(n);
    return head;
}

int main()
{
    ListNode *head;

    for (size_t i = 1; i < 11; i++)
    {
        head = insertNode(head, i);
    }

    head = removeNthFromEnd(head, -1);

    ListNode *temp = head;

    while (temp != nullptr)
    {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    return 0;
}