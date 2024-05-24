#include "Counter.h"

// Counter Member Functions
Counter::Counter() : numKeys(0), totalValue(0), buckets(new Bucket *[8])
{
    for (size_t i = 0; i < 8; i++)
    {
        buckets[i] = new Bucket();
    }
}

Counter::~Counter()
{
    for (size_t i = 0; i < 8; i++)
    {
        delete buckets[i];
    }
}

size_t Counter::count() const { return numKeys; }
int Counter::total() const { return totalValue; }

void Counter::inc(const std::string &key, int by)
{
    totalValue += by;
    List::Node *currNode = keysList.find(key);
    if (currNode)
    {
        currNode->value += by;
    }
    else
    {
        ++numKeys;
        keysList.insert(key, by);
    }
}
void Counter::dec(const std::string &key, int by)
{
    totalValue -= by;
    List::Node *currNode = keysList.find(key);
    if (currNode)
    {
        currNode->value -= by;
    }
    else
    {
        ++numKeys;
        keysList.insert(key, by * -1);
    }
}
void Counter::del(const std::string &key)
{
    --numKeys;
    totalValue -= keysList.find(key)->value;
    keysList.remove(key);
}
int Counter::get(const std::string &key) const
{
    List::Node *currNode = keysList.find(key);
    if (currNode)
    {
        return currNode->value;
    }
    return 0;
}
void Counter::set(const std::string &key, int count)
{
    totalValue += count;
    Bucket *currBucket = nullptr;
    currBucket = buckets[getBucketIndex(key)];
    Bucket::Node *currBucketNode = currBucket->find(key);
    if (currBucketNode)
    {
        List::Node *currListNode = currBucketNode->nodePtr;
        totalValue -= currListNode->value;
        currListNode->value = count;
    }
    else
    {
        currBucket->insert(keysList.insert(key, count));
        numKeys++;
    }
}

Counter::Iterator Counter::begin() const { return Iterator(keysList.first()); }
Counter::Iterator Counter::end() const { return Iterator(nullptr); }