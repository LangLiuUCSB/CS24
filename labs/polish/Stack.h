#ifndef STACK_H
#define STACK_H

#include "Nodes.h"

class Stack
{
private:
    struct Frame
    {
        AST *nodePtr;
        Frame *next;
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
