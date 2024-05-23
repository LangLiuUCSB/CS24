#include "List.h"

// List Member Functions
List::List() : head(nullptr), tail(nullptr), size(0) {}

List::~List()
{
    Node *currNode = head;
    while (currNode)
    {
        Node *tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;
    }
}

Node *List::insert(const std::string &key, int value)
{
    Node *newNode = new Node(key, value);
    if (!tail)
    {
        head = newNode;
        head = tail;
    }
    else
    {
        tail->next = newNode;
        tail->next->prev = tail;
        tail = tail->next;
    }
    return tail;
}
Node *List::find(const std::string &key) const
{
    Node *currNode = head;
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
Node *List::remove(const std::string &key)
{
    Node *currNode = head;
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
            Node *removedNode = currNode;
            currNode = currNode->next;
            removedNode->next = removedNode->prev = nullptr;
            return removedNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}