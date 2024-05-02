#ifndef NODE_H
#define NODE_H

#include <string>

struct Node
{
  std::string data;
  Node *left;
  Node *right;
  size_t weight;

  Node();

  Node(const std::string &s);

  Node *next(const std::string &s) const;
};

#endif
