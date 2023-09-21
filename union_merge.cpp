/**
 * @brief Implementation of unionLinkedList and mergeLinkedList functions
 */
// You must complete the TODO parts and then complete LinkedList.cpp. Delete "TODO" after you are done.

#include "linkedlist.h"

/**
 * @brief Assume two linked lists that represent Set A and Set B respectively.
 * Compute the union A U B and return the result as a new linked list.
 *
 * @param LA Input linkedlist A as a set (no duplicated element)
 * @param LB Input linkedlist B as a set (no duplicated element)
 * @return LinkedList return the unioned linkedlist
 */
LinkedList unionLinkedList(const LinkedList &LA, const LinkedList &LB)
{
    Node *ptr = LB._front;
    LinkedList tmp = LinkedList(LA);

    while (ptr != nullptr)
    {
        if (!tmp.search(ptr->val))
            tmp.addRear(ptr->val);
        ptr = ptr->next;
    }
    return tmp;
}

/**
 * @brief Assume two input linked lists, LA and LB, whose elements are both in the non-descending order.
 * This function merges LA and LB into a new linked list (as the return value).
 * The elements in the new list should still be in the non-descending order.
 *
 * @param LA
 * @param LB
 * @return LinkedList
 */
LinkedList mergeLinkedList(const LinkedList &LA, const LinkedList &LB)
{
    LinkedList mergedList;
    Node *ptrA = LA._front;
    Node *ptrB = LB._front;

    while (ptrA != nullptr && ptrB != nullptr)
    {
        if (ptrA->val <= ptrB->val)
        {
            mergedList.addRear(ptrA->val);
            ptrA = ptrA->next;
        }
        else
        {
            mergedList.addRear(ptrB->val);
            ptrB = ptrB->next;
        }
    }
    while (ptrA != nullptr)
    {
        mergedList.addRear(ptrA->val);
        ptrA = ptrA->next;
    }
    while (ptrB != nullptr)
    {
        mergedList.addRear(ptrB->val);
        ptrB = ptrB->next;
    }
    return mergedList;
}
