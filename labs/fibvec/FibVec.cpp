#include "FibVec.h"

// This provides exception types:
#include <stdexcept>

// FibVec Function Implementations

// Helper Functions
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

// Constructor and Destructor
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

// Member Functions
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
    vec[index] = value;
}
int FibVec::lookup(unsigned long index) const
{
    return vec[index];
}
int FibVec::pop()
{
    vecCount--;
    return -1;
    // return vec[vecCount + 1];
}
void FibVec::push(int value)
{
    if (vecSize == vecCount)
    {
        int *temp = new int[Fib(nthFib + 1)];
        nthFib++;
        for (unsigned long i = 0; i < vecSize; i++)
        {
            temp[i] = vec[i];
        }
        delete[] vec;
        vec = temp;
        vecSize = Fib(nthFib + 1);
    }
    vec[vecCount] = value;
    vecCount++;
}
int FibVec::remove(unsigned long index)
{
    return -1;
}