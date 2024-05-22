#ifndef LIST_H
#define LIST_H

#include <string>
class List
{
    struct Node
    {
        std::string key;
        int data;
        Node *next;
        Node *prev;
        Node(const std::string &key, int data) : key(key), data(data), next(nullptr), prev(nullptr) {}
    };

    Node *head;
    Node *tail;
    size_t size;

public:
    // Constructor
    List();
    ~List();
    void append(const std::string &key, int data);
    Node *find(const std::string &key);
    Node *remove(const std::string &key);
};
#endif
