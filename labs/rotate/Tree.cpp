#include "Tree.h"
#include <iostream>
#include <stdexcept>

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
size_t findH(Node *currNodePtr, const std::string &s, size_t i)
{
    if (currNodePtr == nullptr)
    {
        return (size_t)-1;
    }
    if (currNodePtr->right != nullptr)
    {
        i -= currNodePtr->right->weight;
    }
    if (s == currNodePtr->data)
    {
        return i;
    }
    if (s < currNodePtr->data)
    {
        return findH(currNodePtr->left, s, i - 1);
    }
    else
    {
        return findH(currNodePtr->right, s, currNodePtr->weight - 1);
    }
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

// Helper function to print the tree in tree notation
void printH(Node *currNodePtr)
{
    if (currNodePtr != nullptr)
    {
        if (currNodePtr->weight != 1)
        {
            std::cout << "(";
        }
        printH(currNodePtr->left);
        if (currNodePtr->left == nullptr && currNodePtr->right != nullptr)
        {
            std::cout << "- ";
        }
        if (currNodePtr->left != nullptr)
        {
            std::cout << " ";
        }
        std::cout << currNodePtr->data;
        if (currNodePtr->right != nullptr)
        {
            std::cout << " ";
        }
        printH(currNodePtr->right);
        if (currNodePtr->left != nullptr && currNodePtr->right == nullptr)
        {
            std::cout << " -";
        }
        if (currNodePtr->weight != 1)
        {
            std::cout << ")";
        }
    }
}

// Helper function to find the first occurrence of an item
Node *lookupH(Node *currNodePtr, size_t index, size_t currIndex)
{
    if (currNodePtr->right != nullptr)
    {
        currIndex -= currNodePtr->right->weight;
    }
    if (currIndex == index)
    {
        return currNodePtr;
    }
    if (currIndex > index)
    {
        return lookupH(currNodePtr->left, index, currIndex - 1);
    }
    else
    {
        return lookupH(currNodePtr->right, index, currNodePtr->weight - 1);
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
    if (rootNodePtr == nullptr)
    {
        return 0;
    }
    return rootNodePtr->weight;
}
bool Tree::contains(const std::string &s) const
{
    if (rootNodePtr == nullptr)
    {
        return false;
    }
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
    if (rootNodePtr == nullptr || index >= rootNodePtr->weight)
    {
        throw std::out_of_range("Index out of Range of Tree");
    }
    return lookupH(rootNodePtr, index, rootNodePtr->weight - 1)->data;
}
void Tree::print() const
{
    if (rootNodePtr != nullptr)
    {
        printH(rootNodePtr);
    }
    std::cout << '\n';
}
void Tree::remove(size_t index)
{
}