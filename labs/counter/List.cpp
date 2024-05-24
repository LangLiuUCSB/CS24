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
    if (!head)
    {
        head = new Node(key, value);
        tail = head;
    }
    else
    {
        tail->next = new Node(key, value);
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
            delete currNode;
            return removedNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}
void List::append(Node *nodePtr)
{
    if (!head)
    {
        head = nodePtr;
        tail = head;
    }
    else
    {
        tail->next = nodePtr;
        tail->next->prev = tail;
        tail = tail->next;
    }
}
Node *List::dig(const std::string &key) const
{
    Node *currNode = head;
    while (currNode)
    {
        if (currNode->key == key)
        {
            return currNode;
        }
        currNode = currNode->down;
    }
    return nullptr;
}
