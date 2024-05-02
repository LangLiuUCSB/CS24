#include "Tree.h"
#include <iostream>

//! Helpers
// Helper function to insert a new node
Node *insertH(Node *currNodePtr, const std::string &s)
{
    if (currNodePtr == nullptr)
    {
        return new Node(s);
    }
    currNodePtr->weight++;
    if (s < currNodePtr->data)
    {
        currNodePtr->left = insertH(currNodePtr->left, s);
    }
    else
    {
        currNodePtr->right = insertH(currNodePtr->right, s);
    }
    return currNodePtr;
}

// Helper function to find the first occurrence of an item
size_t findH(Node *currNodePtr, const std::string &s, size_t index)
{
    if (currNodePtr == nullptr)
    {
        return (size_t)-1;
    }
    if (currNodePtr->right != nullptr)
    {
        index -= currNodePtr->right->weight;
    }
    if (s == currNodePtr->data)
    {
        return index;
    }
    else
    {
        if (s < currNodePtr->data)
        {
            return findH(currNodePtr->left, s, index - 1);
        }
        else
        {
            return findH(currNodePtr->right, s, currNodePtr->weight - 1);
        }
    }
    return 1;
}

// Helper function to clear the tree
void clearH(Node *currNodePtr)
{
    if (currNodePtr != nullptr)
    {
        clearH(currNodePtr->left);
        clearH(currNodePtr->right);
        delete currNodePtr;
    }
}

//! Tree Function Implementations
Tree::Tree()
{
    rootNodePtr = nullptr;
}
Tree::~Tree()
{
    clearH(rootNodePtr);
}
void Tree::clear()
{
    clearH(rootNodePtr);
    rootNodePtr = nullptr;
}
size_t Tree::count() const
{
    return rootNodePtr->weight;
}
bool Tree::contains(const std::string &s) const
{
    return findH(rootNodePtr, s, rootNodePtr->weight - 1) != (size_t)-1;
}
size_t Tree::find(const std::string &s) const
{
    return findH(rootNodePtr, s, rootNodePtr->weight - 1);
}
void Tree::insert(const std::string &s)
{
    rootNodePtr = insertH(rootNodePtr, s);
}
std::string Tree::lookup(size_t index) const
{
    return "";
}
void Tree::print() const
{
}
void Tree::remove(size_t index)
{
}