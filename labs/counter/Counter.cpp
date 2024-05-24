#include "Counter.h"

// Counter Member Functions
Counter::Counter() : numKeys(0), totalValue(0), buckets(new SLNode *[8]), numBuckets(8) {}

size_t Counter::count() const { return numKeys; }
int Counter::total() const { return totalValue; }

void Counter::inc(const std::string &key, int by)
{
    List::DLNode *currNode = keysList.find(key);
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
    List::DLNode *currNode = keysList.find(key);
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
    List::DLNode *currNode = keysList.find(key);
    --numKeys;
    totalValue -= currNode->value;
    keysList.remove(key);
}
int Counter::get(const std::string &key) const
{
    size_t bucketIndex = getBucketIndex(key);
    SLNode *currNode = buckets[bucketIndex];
    while (currNode)
    {
        if (currNode->data->key == key)
        {
            return currNode->data->value;
        }
        currNode = currNode->next;
    }
    return 0;
}
void Counter::set(const std::string &key, int count)
{
    totalValue += count;
    size_t bucketIndex = getBucketIndex(key);
    if (!buckets[bucketIndex])
    {
        buckets[bucketIndex] = new SLNode(keysList.insert(key, count));
        ++numKeys;
        return;
    }
    SLNode *currNode = buckets[bucketIndex];
    while (currNode->next)
    {
        if (currNode->next->data->key == key)
        {
            totalValue -= currNode->next->data->value;
            currNode->next->data->value = count;
            return;
        }
        currNode = currNode->next;
    }
    currNode->next = new SLNode(keysList.insert(key, count));
    ++numKeys;
}

Counter::Iterator Counter::begin() const { return Iterator(keysList.begin()); }
Counter::Iterator Counter::end() const { return Iterator(nullptr); }