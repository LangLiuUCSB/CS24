#include "Counter.h"

// Counter Member Functions
Counter::Counter() : buckets(new Node *[16]), numBuckets(16), numKeys(0)
{
    for (size_t i = 0; i < 16; ++i)
    {
        buckets[i] = nullptr;
    }
}
Counter::~Counter()
{
    for (size_t i = 0; i < numBuckets; ++i)
    {
        Node *currNode = buckets[i];
        while (currNode)
        {
            Node *tempNode = currNode->next;
            List::Node *removedNode = keysList.remove(currNode->key);
            delete currNode;
            delete removedNode;
            currNode = tempNode;
        }
        buckets[i] = nullptr;
    }
    delete[] buckets;
}

size_t Counter::count() const { return numKeys; }
int Counter::total() const
{
    int sum = 0;
    for (Iterator it = begin(); it != end(); ++it)
    {
        sum += it.value();
    }
    return sum;
}

void Counter::inc(const std::string &key, int by)
{
    List::Node *currNode = keysList.find(key);
    if (!currNode)
    {
        keysList.insert(key, 1);
    }
    else
    {
        currNode->value += by;
    }
}
void Counter::dec(const std::string &key, int by)
{
    List::Node *currNode = keysList.find(key);
    if (!currNode)
    {
        keysList.insert(key, 1);
    }
    else
    {
        currNode->value -= by;
    }
}
void Counter::del(const std::string &key)
{
    size_t index = getBucketIndex(key);
    Node *current = buckets[index];
    Node *prev = nullptr;
    while (current)
    {
        if (current->key == key)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                buckets[index] = current->next;
            }
            List::Node *removedNode = keysList.remove(key);
            delete current;
            delete removedNode;
            --numKeys;
        }
        prev = current;
        current = current->next;
    }
}
int Counter::get(const std::string &key) const
{
    size_t index = getBucketIndex(key);
    Node *currNode = buckets[index];
    while (currNode)
    {
        if (currNode->key == key)
        {
            return currNode->value;
        }
        currNode = currNode->next;
    }
    return 0;
}
void Counter::set(const std::string &key, int count)
{
    size_t index = getBucketIndex(key);
    Node *currNode = buckets[index];
    while (currNode)
    {
        if (currNode->key == key)
        {
            currNode->value = count;
            List::Node *listNode = keysList.find(key);
            if (listNode)
            {
                listNode->value = count;
            }
            return;
        }
        currNode = currNode->next;
    }
    Node *newNode = new Node(key, count);
    newNode->listNode = keysList.insert(key, count);
    if (!buckets[index])
    {
        buckets[index] = newNode;
    }
    else
    {
        currNode = buckets[index];
        while (currNode->next)
        {
            currNode = currNode->next;
        }
        currNode->next = newNode;
    }
    ++numKeys;
}

Counter::Iterator Counter::begin() const { return Iterator(keysList.getHead()); }
Counter::Iterator Counter::end() const { return Iterator(keysList.getTail()); }