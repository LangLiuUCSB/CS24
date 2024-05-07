#include "Nodes.h"

#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <cmath>

// This creates the number format the autograder expects:
std::string format(double number)
{
  std::ostringstream stream;
  stream << number;
  return stream.str();
}

// Implement your AST subclasses' member functions here.
ArithNode::ArithNode(const char t, AST *l, AST *r) : type(t), left(l), right(r) {}
ArithNode::~ArithNode()
{
  delete left;
  delete right;
}
std::string ArithNode::prefix() const
{
  std::string s(1, type);
  return s + " " + left->prefix() + " " + right->prefix();
}
std::string ArithNode::postfix() const
{
  std::string s(1, type);
  return left->postfix() + " " + right->postfix() + " " + s;
}
double ArithNode::value() const
{
  switch (type)
  {
  case '+':
    return left->value() + right->value();
  case '-':
    return left->value() - right->value();
  case '*':
    return left->value() * right->value();
  case '/':
    if (right->value() == 0.0)
    {
      throw std::runtime_error("Division by zero.");
    }
    return left->value() / right->value();
  case '%':
    if (right->value() == 0.0)
    {
      throw std::runtime_error("Division by zero.");
    }
    return std::fmod(left->value(), right->value());
  }
  return std::numeric_limits<double>::min();
}

NotNode::NotNode(AST *d) : down(d) {}
NotNode::~NotNode() { delete down; }
std::string NotNode::prefix() const { return "~ " + format(down->value()); }
std::string NotNode::postfix() const { return format(down->value()) + " ~"; }
double NotNode::value() const { return down->value() * -1; }

FloatNode::FloatNode(const double n) : number(n) {}
FloatNode::~FloatNode() {}
std::string FloatNode::prefix() const { return format(number); }
std::string FloatNode::postfix() const { return format(number); }
double FloatNode::value() const { return number; }