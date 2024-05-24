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
    List() : head(nullptr), tail(nullptr){};
    ~List();
    Node *first() const { return head; }
    Node *insert(const std::string &key, int value);
    Node *find(const std::string &key) const;
    Node *remove(const std::string &key);

private:
    Node *head;
    Node *tail;
};

class Bucket
{
public:
    struct Node
    {
        List::Node *nodePtr;
        Node *next;
        Node *prev;
        Node(List::Node *n) : nodePtr(n), next(nullptr), prev(nullptr) {}
    };
    Bucket() : head(nullptr), tail(nullptr){};
    ~Bucket();
    Node *first() const { return head; }
    Node *insert(List::Node *n);
    Node *find(const std::string &key) const;
    Node *remove(const std::string &key);

private:
    Node *head;
    Node *tail;
};
#endif
