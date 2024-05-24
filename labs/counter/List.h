#ifndef LIST_H
#define LIST_H

#include <string>

class List
{
public:
    class Node
    {
    public:
        std::string key;
        int value;
        Node *next;
        Node *prev;
        Node(const std::string &k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
    };
    List() : head(nullptr), tail(nullptr){};
    ~List();
    Node *insert(const std::string &key, int value);
    Node *find(const std::string &key) const;
    Node *remove(const std::string &key);
    Node *getHead() const { return head; }
    void setHead(Node *h) { head = h; }
    void setTail(Node *t) { tail = t; }

private:
    Node *head;
    Node *tail;
};

class Bucket
{
public:
    class Node
    {
    public:
        List::Node *nodePtr;
        Node *next;
        Node *prev;
        Node(List::Node *n = nullptr) : nodePtr(n), next(nullptr), prev(nullptr) {}
        void setNode(List::Node *n) { nodePtr = n; }
    };
    Bucket() : head(nullptr), tail(nullptr){};
    ~Bucket();
    Node *first() const { return head; }
    Node *insert(List::Node *n);
    Node *find(const std::string &key) const;
    Node *remove(List::Node *n);

private:
    Node *head;
    Node *tail;
};
#endif
