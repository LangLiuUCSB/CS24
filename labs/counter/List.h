#ifndef LIST_H
#define LIST_H

#include <string>

struct Node
{
    std::string key;
    int value;
    Node *next;
    Node *prev;
    Node *down;
    Node(const std::string &k, int v) : key(k), value(v), next(nullptr), prev(nullptr), down(nullptr) {}
};
class List
{
public:
    List();
    ~List();
    Node *begin() const { return head; }
    Node *end() const { return tail; }
    Node *insert(const std::string &key, int value);
    Node *find(const std::string &key) const;
    Node *remove(const std::string &key);
    void append(Node *nodePtr);

private:
    Node *head;
    Node *tail;
    size_t size;
};
#endif
