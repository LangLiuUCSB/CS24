#include "AST.h"
#include "Nodes.h"
#include "Stack.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

bool isArithOp(const std::string &str)
{
    return (str == "+" || str == "-" || str == "*" || str == "/" || str == "%");
}

bool isDecimal(const std::string &str)
{
    if (str.size())
    {
        char *endPtr;
        std::strtod(str.c_str(), &endPtr);
        return *endPtr == '\0';
    }
    return false;
}

AST *AST::parse(const std::string &expression)
{
    std::string token;
    std::istringstream stream(expression);
    Stack stack;
    AST *currNode;

    while (stream >> token)
    {
        if (isArithOp(token))
        {
            if (stack.size() < 2)
            {
                throw std::runtime_error("Not enough operands.");
            }
            AST *operand2 = stack.pop();
            AST *operand1 = stack.pop();
            currNode = new ArithNode(token[0], operand1, operand2);
        }
        else if (token == "~")
        {
            if (stack.size() < 1)
            {
                throw std::runtime_error("Not enough operands.");
            }
            currNode = new NotNode(stack.pop());
        }
        else if (isDecimal(token))
        {
            currNode = new FloatNode(std::stod(token));
        }
        else
        {
            throw std::runtime_error("Invalid token: " + token);
        }
        stack.push(currNode);
    }
    if (stack.size() < 1)
    {
        throw std::runtime_error("No input.");
    }
    if (stack.size() > 1)
    {
        while (stack.size() != 0)
        {
            stack.pop();
        }
        throw std::runtime_error("Too many operands.");
    }
    return stack.pop();
}
