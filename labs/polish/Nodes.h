#ifndef NODES_H
#define NODES_H

#include "AST.h"

class ArithNode : public AST
{
public:
    ArithNode(const char &t, AST *l = nullptr, AST *r = nullptr);
    ~ArithNode();
    std::string prefix() const;
    std::string postfix() const;
    double value() const;

private:
    char type;
    AST *left;
    AST *right;
};

class NotNode : public AST
{
public:
    NotNode(AST *d = nullptr);
    ~NotNode();
    std::string prefix() const;
    std::string postfix() const;
    double value() const;

private:
    AST *down;
};

class FloatNode : public AST
{
public:
    FloatNode(const double &n);
    ~FloatNode();
    std::string prefix() const;
    std::string postfix() const;
    double value() const;

private:
    double number;
};

#endif
