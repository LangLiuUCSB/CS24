#ifndef LIST_H
#define LIST_H

#include <string>
class List
{
public:
    struct Node
    {
        std::string key;
        int value;
        Node *next;
        Node *prev;
        Node(const std::string &k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
    };
    // Constructor
    List();
    ~List();
    Node *insert(const std::string &key, int value);
    Node *find(const std::string &key);
    Node *remove(const std::string &key);
    Node *getHead() const { return head; }
    Node *getTail() const { return tail; }

private:
    Node *head;
    Node *tail;
    size_t size;
};
#endif
