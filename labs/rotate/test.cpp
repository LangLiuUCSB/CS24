#include "Tree.h"
#include <iostream>

int main()
{
  Tree tree;

  tree.insert("red");
  tree.insert("orange");
  tree.insert("yellow");
  tree.insert("green");
  tree.insert("blue");
  tree.insert("indigo");
  tree.insert("violet");

  std::cout << tree.find("red") << ": " << tree.rootNodePtr->data << "\n";
  std::cout << tree.find("orange") << ": " << tree.rootNodePtr->left->data << "\n";
  std::cout << tree.find("yellow") << ": " << tree.rootNodePtr->right->data << "\n";
  std::cout << tree.find("green") << ": " << tree.rootNodePtr->left->left->data << "\n";
  std::cout << tree.find("blue") << ": " << tree.rootNodePtr->left->left->left->data << "\n";
  std::cout << tree.find("indigo") << ": " << tree.rootNodePtr->left->left->right->data << "\n";
  std::cout << tree.find("violet") << ": " << tree.rootNodePtr->right->left->data << "\n";
  std::cout << tree.find("white") << ": white\n";

  tree.clear();

  std::cout << tree.rootNodePtr << '\n';

  return 0;
}
