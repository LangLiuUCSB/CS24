#include "Heap.h"

#include <stdexcept>

void percolate_down(Heap::Entry *data, size_t count, size_t index)
{
    size_t indexLeftChild = 2 * index + 1;
    size_t indexRightChild = 2 * index + 2;
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
    if (index != 0)
    {
        size_t indexParent = (index - 1) / 2;
        if (data[indexParent].score > data[index].score)
        {
            Heap::Entry tempEntry = data[index];
            data[index] = data[indexParent];
            data[indexParent] = tempEntry;
            percolate_up(data, count, indexParent);
        }
    }
}

Heap::Heap(size_t capacity) : mData(new Entry[capacity]), mCapacity(capacity), mCount(0) {}
Heap::Heap(const Heap &other) : mData(new Entry[other.capacity()]), mCapacity(other.capacity()), mCount(other.count())
{
    for (size_t i = 0; i < mCapacity; i++)
    {
        mData[i] = other.mData[i];
    }
}
Heap::~Heap() { delete[] mData; }

size_t Heap::capacity() const { return mCapacity; }
size_t Heap::count() const { return mCount; }
const Heap::Entry &Heap::lookup(size_t index) const
{
    if (index >= mCount)
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
    Entry tempEntry = mData[0];
    mData[0] = mData[mCount - 1];
    --mCount;
    percolate_down(mData, mCount, 0);
    return tempEntry;
}
Heap::Entry Heap::pushpop(const std::string &value, float score)
{
    if (mCount == 0)
    {
        throw std::underflow_error("Heap Empty");
    }
    Entry tempEntry = mData[0];
    mData[0].value = value;
    mData[0].score = score;
    percolate_down(mData, mCount, 0);
    return tempEntry;
}
void Heap::push(const std::string &value, float score)
{
    if (mCount == mCapacity)
    {
        throw std::overflow_error("Heap Full");
    }
    ++mCount;
    mData[mCount - 1].value = value;
    mData[mCount - 1].score = score;
    percolate_up(mData, mCount, mCount - 1);
}
const Heap::Entry &Heap::top() const
{
    if (mCount == 0)
    {
        throw std::underflow_error("Heap Empty");
    }
    return mData[0];
}
