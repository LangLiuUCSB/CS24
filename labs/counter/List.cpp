#include "List.h"

// List Member Functions
List::List() : head(nullptr), tail(nullptr), size(0) {}

List::~List()
{
    List::Node *currNode = head;
    while (currNode != nullptr)
    {
        delete currNode;
        currNode = currNode->next;
    }
}

void List::append(const std::string &key, int data)
{
    if (tail == nullptr)
    {
        tail = new List::Node(key, data);
        head = tail;
    }
    else
    {
        tail->next = new List::Node(key, data);
        tail = tail->next;
    }
}
List::Node *List::find(const std::string &key)
{
    List::Node *currNode = head;
    while (currNode->key != key && currNode != nullptr)
    {
        currNode = currNode->next;
    }
    return currNode;
}
List::Node *List::remove(const std::string &key)
{
    List::Node *currNode = head;
    while (currNode->key != key && currNode != nullptr)
    {
        currNode = currNode->next;
    }
    List::Node *prevNode = currNode->prev;
    List::Node *nextNode = currNode->next;
    prevNode->next = nextNode;
    nextNode->prev = nextNode;
    delete currNode;
    return currNode;
}