#include "Tree.h"
#include <iostream>
#include <stdexcept>

//! Helpers
Node *balance(Node *currNodePtr, size_t i)
{
    size_t leftWeight = 0;
    size_t rightWeight = 0;
    if (currNodePtr->left != nullptr)
    {
        leftWeight = currNodePtr->left->weight;
    }
    if (currNodePtr->right != nullptr)
    {
        rightWeight = currNodePtr->right->weight;
    }
    // std::cout << leftWeight << " " << i << currNodePtr->data << i << " " << rightWeight << ", ";
    if (leftWeight > rightWeight + 1)
    {
        Node *tempNodePtr = currNodePtr;
        currNodePtr->left->weight = currNodePtr->weight;
        currNodePtr = currNodePtr->left;
        tempNodePtr->left = currNodePtr->right;
        currNodePtr->right = tempNodePtr;
        tempNodePtr->weight = 1;
        if (tempNodePtr->left != nullptr)
        {
            tempNodePtr->weight += tempNodePtr->left->weight;
        }
        tempNodePtr->weight += rightWeight;
    }
    if (rightWeight > leftWeight + 1)
    {
        Node *tempNodePtr = currNodePtr;
        currNodePtr->right->weight = currNodePtr->weight;
        currNodePtr = currNodePtr->right;
        tempNodePtr->right = currNodePtr->left;
        currNodePtr->left = tempNodePtr;
        tempNodePtr->weight = 1;
        if (tempNodePtr->right != nullptr)
        {
            tempNodePtr->weight += tempNodePtr->right->weight;
        }
        tempNodePtr->weight += leftWeight;
    }
    return currNodePtr;
}

// Helper function to insert a new node
Node *insertH(Node *currNodePtr, const std::string &s)
{
    if (currNodePtr == nullptr)
    {
        return new Node(s);
    }
    currNodePtr->weight++;
    if (s <= currNodePtr->data)
    {
        currNodePtr->left = insertH(currNodePtr->left, s);
        currNodePtr->left = balance(currNodePtr->left, 0);
    }
    else
    {
        currNodePtr->right = insertH(currNodePtr->right, s);
        currNodePtr->right = balance(currNodePtr->right, 0);
    }
    return currNodePtr;
}

// TODO: find s at smallest index that exists
// Helper function to find the first occurrence of an item
size_t findH(Node *currNodePtr, const std::string &s, size_t currIndex)
{
    if (currNodePtr == nullptr)
    {
        return (size_t)-1;
    }
    if (currNodePtr->right != nullptr)
    {
        currIndex -= currNodePtr->right->weight;
    }
    if (s == currNodePtr->data)
    {
        return currIndex;
    }
    if (s < currNodePtr->data)
    {
        return findH(currNodePtr->left, s, currIndex - 1);
    }
    if (currNodePtr->right != nullptr)
    {
        return findH(currNodePtr->right, s, currIndex + currNodePtr->right->weight);
    }
    return findH(currNodePtr->right, s, currIndex);
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

// Helper function to print the tree in in-order traversal notation
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

// Helper function to find the string stored at an index
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
    return lookupH(currNodePtr->right, index, currIndex + currNodePtr->right->weight);
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
    if (rootNodePtr != nullptr)
    {
        clearH(rootNodePtr);
        rootNodePtr = nullptr;
    }
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
    if (rootNodePtr == nullptr)
    {
        return (size_t)-1;
    }
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
    if (rootNodePtr == nullptr)
    {
        std::cout << "-\n";
    }
    else
    {
        printH(rootNodePtr);
        std::cout << '\n';
    }
}
void Tree::remove(size_t index)
{
}

/*
    size_t leftWeight = 0;
    size_t rightWeight = 0;
    if (rootNodePtr->left != nullptr)
    {
        leftWeight = rootNodePtr->left->weight;
    }
    if (rootNodePtr->right != nullptr)
    {
        rightWeight = rootNodePtr->right->weight;
    }
    if (leftWeight > rightWeight + 1)
    {
        Node *tempNodePtr = rootNodePtr;
        rootNodePtr->left->weight = rootNodePtr->weight;
        rootNodePtr = rootNodePtr->left;
        tempNodePtr->left = rootNodePtr->right;
        rootNodePtr->right = tempNodePtr;
        tempNodePtr->weight = 1;
        if (tempNodePtr->left != nullptr)
        {
            tempNodePtr->weight += tempNodePtr->left->weight;
        }
        if (tempNodePtr->right != nullptr)
        {
            tempNodePtr->weight += tempNodePtr->right->weight;
        }
    }
*/