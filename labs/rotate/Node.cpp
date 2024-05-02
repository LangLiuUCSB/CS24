#include "Node.h"

Node::Node()
{
    left = nullptr;
    right = nullptr;
    weight = 1;
}
Node::Node(const std::string &s)
{
    data = s;
    left = nullptr;
    right = nullptr;
    weight = 1;
}
