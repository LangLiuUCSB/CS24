#include "Stack.h"

#include <iostream>

Stack::Stack() : topFramePtr(nullptr), count(0) {}
Stack::~Stack() { while (count != 0) { pop(); } }
void Stack::push(AST *inputNodePtr)
{
    count++;
    topFramePtr = new Frame{inputNodePtr, topFramePtr};
}
AST *Stack::pop()
{
    count--;
    if (topFramePtr == nullptr)
    {
        std::cerr << "Error: Cannot pop empty stack.\n";
        return nullptr;
    }
    else
    {
        AST *output = topFramePtr->nodePtr;
        Frame *temp = topFramePtr;
        topFramePtr = topFramePtr->next;
        delete temp;
        return output;
    }
}
size_t Stack::size() const { return count; }