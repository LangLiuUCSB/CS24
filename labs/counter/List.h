#ifndef LIST_H
#define LIST_H

#include <string>
class Node
{
public:
    std::string key;
    int value;
    Node *next;
    Node *prev;
    Node(const std::string &k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
};
class List
{
public:
    // Constructor
    List();
    ~List();
    Node *insert(const std::string &key, int value);
    Node *find(const std::string &key) const;
    Node *remove(const std::string &key);
    Node *begin() const { return head; }
    Node *end() const { return tail; }

private:
    Node *head;
    Node *tail;
    size_t size;
};
#endif
