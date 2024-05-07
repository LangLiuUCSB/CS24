#ifndef STACK_H
#define STACK_H

#include "Nodes.h"
// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

class Stack
{
private:
    struct Frame
    {
        AST *nodePtr;
        Frame *next;
        ~Frame() { delete nodePtr; }
    };
    Frame *topFramePtr;
    size_t count;

public:
    Stack();
    ~Stack();
    void push(AST *inputNodePtr);
    AST *pop();
    size_t size() const;
};

#endif
