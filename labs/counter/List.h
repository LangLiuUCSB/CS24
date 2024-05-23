#ifndef LIST_H
#define LIST_H

#include <string>

class List
{
public:
    class DLNode
    {
    public:
        std::string key;
        int value;
        DLNode *next;
        DLNode *prev;
        DLNode(const std::string &k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
    };
    // Constructor
    List();
    ~List();
    DLNode *insert(const std::string &key, int value);
    DLNode *find(const std::string &key) const;
    DLNode *remove(const std::string &key);
    DLNode *begin() const { return head; }
    DLNode *end() const { return tail; }

private:
    DLNode *head;
    DLNode *tail;
    size_t size;
};
#endif
