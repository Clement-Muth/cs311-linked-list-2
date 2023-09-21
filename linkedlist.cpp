// INSTRUCTION:
// It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//   Highly recommended to copy HW3P1-help as PURPOSE of each function.
//   Add sufficient comments to your code body to describe what it does.
//       - Make sure all if-then-else are commented describing which case it is
//       - Make sure all local variables are described fully with their purposes

// You must complete the TODO parts and then complete LinkedList.cpp. Delete "TODO" after you are done.

// ====================================================
// Your name: Clement Nicolas Denis Muth
// Complier: g++
// File type: linkedList.cpp implementation file
//=====================================================

#include <iostream>
#include "linkedlist.h"

using namespace std;

/**
 * @brief Destructor to destroy all nodes and release memory
 */
LinkedList::~LinkedList()
{
    Node *temp = _front;

    if (_front == nullptr)
        return;
    while (_front != nullptr)
    {
        temp = _front;
        _front = _front->next;
        delete temp;
    }
}

/**
 * @brief Purpose: Checks if the list is empty
 * @return true if the list is empty, false otherwise
 */
bool LinkedList::isEmpty() const
{
    return _count == 0;
}

/**
 * @brief  Get the number of nodes in the list
 * @return int The number of nodes in the list
 */
int LinkedList::length() const
{
    return _count;
}

/**
 * @brief Convert the list to a string
 *
 */
string LinkedList::toString()
{
    string str = "[";
    Node *ptr = _front;

    if (ptr != nullptr)
    {
        // Head node is not preceded by separator
        str += to_string(ptr->val);
        ptr = ptr->next;
    }
    while (ptr != nullptr)
    {
        str += ", " + to_string(ptr->val);
        ptr = ptr->next;
    }
    str += "]";
    return str;
}

/**
 * @brief Displays the contents of the list
 */
void LinkedList::displayAll()
{
    cout << toString() << endl;
}

/**
 * @brief Add node to the end of the list
 */
void LinkedList::addRear(T val)
{
    if (_front == nullptr)
    {
        _front = new Node(val);
        _rear = _front;
        _count++;
        return;
    }
    Node *tmp = _front;

    while (tmp->next != nullptr)
        tmp = tmp->next;
    tmp->next = new Node(val);
    _count++;
}

/**
 * @brief Add node to the start of the list
 */
void LinkedList::addFront(T val)
{
    Node *newNode = new Node(val);

    if (_front == nullptr)
    {
        _front = newNode;
        _count++;
        return;
    }
    newNode->next = _front;
    _front = newNode;
    _count++;
}

/**
 * @brief Delete the first node of the list
 * @param oldNum the value of the deleted node
 * @return true if the node was removed or false otherwise
 */
bool LinkedList::deleteFront(T &OldNum)
{
    Node *ptr = _front;

    if (_front == nullptr)
        return false;
    OldNum = _front->val;
    if (_front->next == nullptr)
    {
        delete _front;
        _front = nullptr;
    }
    else
    {
        ptr = _front->next;
        delete _front;
        _front = ptr;
    }
    _count--;
    return true;
}

/**
 * @brief Delete the latest node of the list
 * @param oldNum the value of the deleted node
 * @return true if the node was removed or false otherwise
 */
bool LinkedList::deleteRear(T &OldNum)
{
    Node *ptr = _front;

    if (_front == nullptr)
        return false;
    if (_front->next == nullptr)
    {
        OldNum = _front->val;
        delete _front;
        _rear = _front = nullptr;
        --_count;
        return true;
    };
    while (ptr->next->next != nullptr)
        ptr = ptr->next;
    OldNum = ptr->next->val;
    delete ptr->next;
    ptr->next = nullptr;
    _rear = ptr;
    --_count;
    return true;
}

/* --- harder ones for test 2 and 3 -- */

/**
 * @brief Delete a node at a given position from the list. The
 * node at position pos is deleted and the value of the deleted node is returned in val.
 * The valid range of pos is 0 to count-1. if pos = 0, delete first node, and pos = count-1 delete last node.
 * @param pos: position of the node to be deleted
 * @param val: it is set to the value of the node to be deleted
 * @return true: if the node was deleted successfully
 * @return false: if the node was not deleted successfully because the position was out of range
 */
bool LinkedList::deleteAt(int pos, T &val)
{
    Node *ptr = _front;
    Node *tmp = _front;

    if (OUT_OF_RANGE(pos, _count - 1))
        return false;
    if (pos == 0)
        return deleteFront(val);
    if (pos == _count - 1)
        return deleteRear(val);
    for (int i = 0; i != pos - 1; i++)
        ptr = ptr->next;
    val = ptr->next->val;
    tmp = ptr->next->next;
    delete ptr->next;
    ptr->next = tmp;
    _count--;
    return true;
}

/**
 * @brief Insert a value at a specified position in the list. The valid pos is in the range of 0 to count.
 * The value will be inserted before the node at the specified position. if pos = 0, the value will be inserted
 * at the front of the list. if pos = count, the value will be inserted at the rear of the list.
 * @param pos: position to insert the value at.
 * @param val: value to insert.
 * @return true: if the value was inserted.
 * @return false: if the value was not inserted because pos is out of the range.
 */
bool LinkedList::insertAt(int pos, T val)
{
    Node *ptr = _front;

    if (OUT_OF_RANGE(pos, _count))
        return false;
    if (pos == 0)
    {
        addFront(val);
        return true;
    }
    if (pos == _count)
    {
        addRear(val);
        return true;
    }
    Node *tmp = new Node(val);
    for (int i = 0; i < pos - 1; i++)
        ptr = ptr->next;
    tmp->next = ptr->next;
    ptr->next = tmp;
    _count++;
    return true;
}

/**
 * @brief Copy Constructor to allow pass by value and return by value of a LinkedList
 * @param other LinkedList to be copied
 */
LinkedList::LinkedList(const LinkedList &other)
{
    Node *otherPtr = other._front;

    _front = new Node(other._front->val);
    _rear = nullptr;
    _count = 0;
    otherPtr = otherPtr->next;
    while (otherPtr != nullptr)
    {
        addRear(otherPtr->val);
        otherPtr = otherPtr->next;
        _count++;
    }
}

/**
 * @brief Overloading of = (returns a reference to a LinkedList)
 * @param other LinkedList to be copied
 * @return reference to a LinkedList
 */
LinkedList &LinkedList::operator=(const LinkedList &other)
{
    if (this != &other)
    {
        Node *otherPtr = other._front;
        int __x = 0;

        while (_front != nullptr)
            deleteFront(__x);
        _rear = nullptr;
        _front = new Node(other._front->val);
        _count = 1;
        otherPtr = otherPtr->next;
        while (otherPtr != nullptr)
        {
            addRear(otherPtr->val);
            otherPtr = otherPtr->next;
        }
    }
    return *this;
}

/**
 * @brief check whether a value is in the list or not
 * @param val
 * @return true if the val is found in the list, false otherwise
 */
bool LinkedList::search(T val) const
{
    Node *current = _front;

    while (current != nullptr)
    {
        if (current->val == val)
            return true;
        current = current->next;
    }
    return false;
}