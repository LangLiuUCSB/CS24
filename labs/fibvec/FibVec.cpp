#include "FibVec.h"
#include <iostream>

// This provides exception types:
#include <stdexcept>

// FibVec Function Implementations
size_t FibVec::Fib(size_t n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    return Fib(n - 1) + Fib(n - 2);
}
FibVec::FibVec()
{
    vec = new int[1];
    vecSize = 1;
    vecCount = 0;
    nthFib = 2;
}
FibVec::~FibVec()
{
    delete[] vec;
}
unsigned long FibVec::capacity() const
{
    return vecSize;
}
unsigned long FibVec::count() const
{
    return vecCount;
}
void FibVec::insert(int value, unsigned long index)
{
    if (index > vecCount)
    {
        throw std::out_of_range("Index out of Vector Range");
    }
    vecCount++;
    unsigned long i;
    if (vecCount > vecSize)
    {
        nthFib++;
        unsigned long vecSizeNext = Fib(nthFib);
        int *temp = new int[vecSizeNext];
        for (i = 0; i < vecSize; i++)
        {
            temp[i] = vec[i];
        }
        delete[] vec;
        vec = temp;
        vecSize = vecSizeNext;
    }
    for (i = vecCount - 1; i > index; i--)
    {
        vec[i] = vec[i - 1];
    }
    vec[index] = value;
}
int FibVec::lookup(unsigned long index) const
{
    if (index + 1 > vecCount)
    {
        throw std::out_of_range("Index out of Vector Range");
    }
    return vec[index];
}
int FibVec::pop()
{
    if (vecCount == 0)
    {
        throw std::underflow_error("Vector Already Empty");
    }
    vecCount--;
    int poppedValue = vec[vecCount];
    unsigned long vecSizePrev = Fib(nthFib - 1);
    if (vecCount + vecSizePrev < vecSize)
    {
        nthFib--;
        int *temp = new int[vecSizePrev];
        for (unsigned long i = 0; i < vecSizePrev; i++)
        {
            temp[i] = vec[i];
        }
        delete[] vec;
        vec = temp;
        vecSize = vecSizePrev;
    }
    return poppedValue;
}
void FibVec::push(int value)
{
    vecCount++;
    if (vecCount > vecSize)
    {
        nthFib++;
        unsigned long vecSizeNext = Fib(nthFib);
        int *temp = new int[vecSizeNext];
        for (unsigned long i = 0; i < vecSize; i++)
        {
            temp[i] = vec[i];
        }
        delete[] vec;
        vec = temp;
        vecSize = vecSizeNext;
    }
    vec[vecCount - 1] = value;
}
int FibVec::remove(unsigned long index)
{
    if (index + 1 > vecCount)
    {
        throw std::out_of_range("Index out of Vector Range");
    }
    vecCount--;
    unsigned long i;
    int removedValue = vec[index];
    for (i = index; i < vecCount; i++)
    {
        vec[i] = vec[i + 1];
    }
    unsigned long vecSizePrev = Fib(nthFib - 1);
    if (vecCount + vecSizePrev < vecSize)
    {
        nthFib--;
        int *temp = new int[vecSizePrev];
        for (unsigned long i = 0; i < vecSizePrev; i++)
        {
            temp[i] = vec[i];
        }
        delete[] vec;
        vec = temp;
        vecSize = vecSizePrev;
    }
    return removedValue;
}