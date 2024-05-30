#include "Heap.h"

#include <stdexcept>

void percolate_down(Heap::Entry *data, size_t count, size_t index)
{
    size_t indexLeftChild = 2 * index;
    size_t indexRightChild = 2 * index + 1;
    size_t indexSmallest = index;
    if (indexLeftChild < count && data[indexLeftChild].score < data[indexSmallest].score)
    {
        indexSmallest = indexLeftChild;
    }
    if (indexRightChild < count && data[indexRightChild].score < data[indexSmallest].score)
    {
        indexSmallest = indexRightChild;
    }
    if (indexSmallest != index)
    {
        Heap::Entry tempEntry = data[index];
        data[index] = data[indexSmallest];
        data[indexSmallest] = tempEntry;
        percolate_down(data, count, indexSmallest);
    }
}

void percolate_up(Heap::Entry *data, size_t count, size_t index)
{
    if (index != 1)
    {
        size_t indexParent = index / 2;
        if (data[indexParent].score < data[index].score)
        {
            Heap::Entry tempEntry = data[index];
            data[index] = data[indexParent];
            data[indexParent] = tempEntry;
            percolate_up(data, count, indexParent);
        }
    }
}

Heap::Heap(size_t capacity) : mData(new Entry[capacity + 1]), mCapacity(capacity), mCount(0) {}
Heap::Heap(const Heap &other) : mData(new Entry[other.capacity() + 1]), mCapacity(other.capacity()), mCount(other.count())
{
    for (size_t i = 1; i <= mCapacity; i++)
    {
        mData[i] = other.mData[i];
    }
}
Heap::~Heap() { delete mData; }

size_t Heap::capacity() const { return mCapacity; }
size_t Heap::count() const { return mCount; }
const Heap::Entry &Heap::lookup(size_t index) const
{
    if (index > mCount)
    {
        throw std::out_of_range("Index out of Heap Range");
    }
    return mData[index];
}
Heap::Entry Heap::pop()
{
    if (mCount == 0)
    {
        throw std::underflow_error("Heap Empty");
    }
    Entry tempEntry = mData[1];
    mData[1] = mData[mCount];
    --mCount;
    percolate_down(mData, mCount, 1);
    return tempEntry;
}
Heap::Entry Heap::pushpop(const std::string &value, float score)
{
    if (mCount == 0)
    {
        throw std::underflow_error("Heap Empty");
    }
    Entry tempEntry = mData[1];
    mData[1].value = value;
    mData[1].score = score;
    percolate_down(mData, mCount, 1);
    return tempEntry;
}
void Heap::push(const std::string &value, float score)
{
    if (mCount == mCapacity)
    {
        throw std::overflow_error("Heap Full");
    }
    ++mCount;
    mData[mCount].value = value;
    mData[mCount].score = score;
    percolate_up(mData, mCount, mCount);
}
const Heap::Entry &Heap::top() const
{
    if (mCount == 0)
    {
        throw std::underflow_error("Heap Empty");
    }
    return mData[1];
}
