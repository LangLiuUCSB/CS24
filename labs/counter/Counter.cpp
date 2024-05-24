#include "Counter.h"

// Counter Member Functions
Counter::Counter() : numKeys(0), totalValue(0), numBuckets(10000)
{
    buckets = new Bucket *[numBuckets];
    for (size_t i = 0; i < numBuckets; ++i)
    {
        buckets[i] = new Bucket();
    }
}

Counter::~Counter()
{
    for (size_t i = 0; i < numBuckets; ++i)
    {
        delete buckets[i];
    }
    delete[] buckets;
}

size_t Counter::count() const { return numKeys; }
int Counter::total() const { return totalValue; }

void Counter::inc(const std::string &key, int by)
{
    size_t bucketIndex = getBucketIndex(key);
    Bucket *currBucket = buckets[bucketIndex];
    Bucket::Node *currBucketNode = currBucket->find(key);

    if (currBucketNode)
    {
        currBucketNode->nodePtr->value += by;
    }
    else
    {
        List::Node *newNode = keysList.insert(key, by);
        currBucket->insert(newNode);
        ++numKeys;
    }

    totalValue += by;
}
void Counter::dec(const std::string &key, int by)
{
    size_t bucketIndex = getBucketIndex(key);
    Bucket *currBucket = buckets[bucketIndex];
    Bucket::Node *currBucketNode = currBucket->find(key);

    if (currBucketNode)
    {
        currBucketNode->nodePtr->value -= by;
    }
    else
    {
        List::Node *newNode = keysList.insert(key, -by);
        currBucket->insert(newNode);
        ++numKeys;
    }

    totalValue -= by;
}
void Counter::del(const std::string &key)
{
    size_t bucketIndex = getBucketIndex(key);
    Bucket *currBucket = buckets[bucketIndex];
    Bucket::Node *currBucketNode = currBucket->find(key);

    if (currBucketNode)
    {
        List::Node *currListNode = currBucketNode->nodePtr;

        totalValue -= currListNode->value;

        if (currListNode->prev)
        {
            currListNode->prev->next = currListNode->next;
        }
        else
        {
            keysList.setHead(currListNode->next);
        }
        if (currListNode->next)
        {
            currListNode->next->prev = currListNode->prev;
        }
        else
        {
            keysList.setTail(currListNode->prev);
        }

        delete currListNode;
        currBucket->remove(currListNode);
        --numKeys;
    }
}
int Counter::get(const std::string &key) const
{
    size_t bucketIndex = getBucketIndex(key);
    Bucket *currBucket = buckets[bucketIndex];
    Bucket::Node *currBucketNode = currBucket->find(key);

    if (currBucketNode)
    {
        return currBucketNode->nodePtr->value;
    }
    return 0;
}
void Counter::set(const std::string &key, int count)
{
    size_t bucketIndex = getBucketIndex(key);
    Bucket *currBucket = buckets[bucketIndex];
    Bucket::Node *currBucketNode = currBucket->find(key);

    if (currBucketNode)
    {
        List::Node *currListNode = currBucketNode->nodePtr;
        totalValue = totalValue - currListNode->value + count;
        currListNode->value = count;
    }
    else
    {
        List::Node *newNode = keysList.insert(key, count);
        currBucket->insert(newNode);
        ++numKeys;
        totalValue += count;
    }
}

Counter::Iterator Counter::begin() const { return Iterator(keysList.getHead()); }
Counter::Iterator Counter::end() const { return Iterator(nullptr); }