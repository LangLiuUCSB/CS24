#include "List.h"

// List Member Functions
List::List() : head(nullptr), tail(nullptr), size(0) {}

List::~List()
{
    DLNode *currNode = head;
    while (currNode)
    {
        DLNode *tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;
    }
}

List::DLNode *List::insert(const std::string &key, int value)
{
    DLNode *newNode = new DLNode(key, value);
    if (!head)
    {
        head = newNode;
        tail = head;
    }
    else
    {
        tail->next = newNode;
        tail->next->prev = tail;
        tail = tail->next;
    }
    return tail;
}
List::DLNode *List::find(const std::string &key) const
{
    DLNode *currNode = head;
    while (currNode)
    {
        if (currNode->key == key)
        {
            return currNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}
List::DLNode *List::remove(const std::string &key)
{
    DLNode *currNode = head;
    while (currNode)
    {
        if (currNode->key == key)
        {
            if (currNode->prev)
            {
                currNode->prev->next = currNode->next;
            }
            else
            {
                head = currNode->next;
            }
            if (currNode->next)
            {
                currNode->next->prev = currNode->prev;
            }
            else
            {
                tail = currNode->prev;
            }
            DLNode *removedNode = currNode;
            delete currNode;
            return removedNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}