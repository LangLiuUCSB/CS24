#include "List.h"

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
List::Node *List::insert(const std::string &key, int value)
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
List::Node *List::find(const std::string &key) const
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
List::Node *List::remove(const std::string &key)
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

Bucket::~Bucket()
{
    Node *currNode = head;
    while (currNode)
    {
        Node *tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;
    }
}
Bucket::Node *Bucket::insert(List::Node *n)
{
    Node *newNode = new Node(n);
    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail->next->prev = tail;
        tail = tail->next;
    }
    return newNode;
}
Bucket::Node *Bucket::find(const std::string &key) const
{
    Node *currNode = head;
    while (currNode)
    {
        if (currNode->nodePtr->key == key)
        {
            return currNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}
Bucket::Node *Bucket::remove(List::Node *n)
{
    Node *currNode = head;
    while (currNode)
    {
        if (currNode->nodePtr == n)
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
