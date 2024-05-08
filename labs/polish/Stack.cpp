#include "Stack.h"

#include <iostream>
void Stack::resize()
{
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
    AST **newElements = new AST *[newCapacity];
    for (size_t i = 0; i < capacity; ++i)
    {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

Stack::Stack() : elements(nullptr), capacity(0), topIndex((size_t)-1) {}
Stack::~Stack()
{
    for (size_t i = 0; i <= topIndex && topIndex != (size_t)-1; ++i)
    {
        delete elements[i];
    }
    delete[] elements;
}
void Stack::push(AST *inputNodePtr)
{
    if (topIndex == capacity - 1)
    {
        resize();
    }
    elements[++topIndex] = inputNodePtr;
}
AST *Stack::pop()
{
    if (topIndex == (size_t)-1)
    {
        throw std::out_of_range("Cannot pop empty stack.");
    }
    return elements[topIndex--];
}
size_t Stack::size() const { return topIndex + 1; }