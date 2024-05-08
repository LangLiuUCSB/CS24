#ifndef STACK_H
#define STACK_H

#include "Nodes.h"

class Stack
{
private:
    AST **elements;
    size_t capacity;
    size_t topIndex;
    void resize();

public:
    Stack();
    ~Stack();
    void push(AST *inputNodePtr);
    AST *pop();
    size_t size() const;
};

#endif
