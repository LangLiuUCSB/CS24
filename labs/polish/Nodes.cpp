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
FloatNode::FloatNode(const double n) : number(n) {}
FloatNode::~FloatNode() {}
std::string FloatNode::prefix() const { return format(number); }
std::string FloatNode::postfix() const { return format(number); }
double FloatNode::value() const { return number; }

ArithNode::ArithNode(const ArithOp t, AST *l, AST *r) : type(t), left(l), right(r) {}
ArithNode::~ArithNode() {}
std::string ArithNode::prefix() const
{
  return "ArithNode::prefix " + format(value());
}
std::string ArithNode::postfix() const
{
  return "ArithNode::postfix" + format(value());
}
double ArithNode::value() const
{
  switch (type)
  {
  case ArithOp::Addition:
    return left->value() + right->value();
  case ArithOp::Subtraction:
    return left->value() - right->value();
  case ArithOp::Multiplication:
    return left->value() * right->value();
  case ArithOp::Division:
    if (right->value() == 0.0)
    {
      throw std::runtime_error("Division by zero.");
    }
    return left->value() / right->value();
  case ArithOp::Modulus:
    return std::fmod(left->value(), right->value());
  }
  return std::numeric_limits<double>::min();
}

NotNode::NotNode(AST *d) : down(d) {}
NotNode::~NotNode() {}
std::string NotNode::prefix() const
{
  return "NotNode::prefix()" + format(value());
}
std::string NotNode::postfix() const
{
  return "NotNode::postfix()" + format(value());
}
double NotNode::value() const
{
  return down->value() * -1;
}