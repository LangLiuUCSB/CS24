#include "Counter.h"

// Counter Member Functions
Counter::Counter() : numKeys(0), totalValue(0) {}

size_t Counter::count() const { return numKeys; }
int Counter::total() const { return totalValue; }

void Counter::inc(const std::string &key, int by)
{
    Node *currNode = keysList.find(key);
    if (currNode)
    {
        currNode->value += by;
    }
    else
    {
        keysList.insert(key, by);
        ++numKeys;
    }
    totalValue += by;
}
void Counter::dec(const std::string &key, int by)
{
    Node *currNode = keysList.find(key);
    if (currNode)
    {
        currNode->value -= by;
    }
    else
    {
        keysList.insert(key, by * -1);
        ++numKeys;
    }
    totalValue -= by;
}
void Counter::del(const std::string &key)
{
    Node *currNode = keysList.find(key);
    --numKeys;
    totalValue -= currNode->value;
    keysList.remove(key);
}
int Counter::get(const std::string &key) const
{
    Node *currNode = keysList.find(key);
    if (currNode != nullptr)
    {
        return currNode->value;
    }
    return 0;
}
void Counter::set(const std::string &key, int count)
{
    Node *currNode = keysList.find(key);
    if (currNode)
    {
        totalValue -= currNode->value;
        currNode->value = count;
    }
    else
    {
        keysList.insert(key, count);
        ++numKeys;
    }
    totalValue += count;
}

Counter::Iterator Counter::begin() const { return Iterator(keysList.begin()); }
Counter::Iterator Counter::end() const { return Iterator(nullptr); }