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

    while (stream >> token)
    {
        AST *currNode;
        if (isArithOp(token))
        {
            // std::cout << "ArithNode\n";
            if (stack.size() < 2)
            {
                delete stack;
                throw std::runtime_error("Not enough operands.");
            }
            AST *operand2 = stack.pop();
            AST *operand1 = stack.pop();
            switch (token[0])
            {
            case '+':
                // std::cout << "+\n";
                currNode = new ArithNode(ArithOp::Addition, operand1, operand2);
                break;
            case '-':
                // std::cout << "-\n";
                currNode = new ArithNode(ArithOp::Subtraction, operand1, operand2);
                break;
            case '*':
                // std::cout << "*\n";
                currNode = new ArithNode(ArithOp::Multiplication, operand1, operand2);
                break;
            case '/':
                // std::cout << "/\n";
                currNode = new ArithNode(ArithOp::Division, operand1, operand2);
                break;
            case '%':
                // std::cout << "%\n";
                currNode = new ArithNode(ArithOp::Modulus, operand1, operand2);
                break;
            }
            // std::cout << "push: " << currNode->value() << "\n";
        }
        else if (token == "~")
        {
            // std::cout << "NotNode\n";
            if (stack.size() < 1)
            {
                delete stack;
                throw std::runtime_error("Not enough operands.");
            }
            currNode = new NotNode(stack.pop());
            // std::cout << "push: " << currNode->value() << "\n";
        }
        else if (isDecimal(token))
        {
            // std::cout << "FloatNode\n";
            currNode = new FloatNode(std::stod(token));
            // std::cout << "push: " << currNode->value() << "\n";
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
        throw std::runtime_error("Too many operands.");
    }

    return stack.pop();
}
