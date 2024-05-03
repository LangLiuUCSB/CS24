#include "Tree.h"
#include <iostream>

int main()
{
  Tree tree;

  tree.print();

  tree.insert("red");
  tree.insert("orange");
  tree.insert("yellow");
  tree.insert("green");
  tree.insert("blue");
  // tree.insert("indigo");
  // tree.insert("violet");

  std::cout << "rootNodePtr: " << tree.rootNodePtr << '\n';

  std::cout << "Tree:\n";
  tree.print();

  for (size_t i = 0; i < 5; i++)
  {
    std::cout << tree.find(tree.lookup(i)) << ": " << tree.lookup(i) << '\n';
  }
  std::cout << tree.find("white") << ": white\n";
  if (tree.contains("white"))
  {
    std::cout << "Tree does constains \"white\"\n";
  }
  else
  {
    std::cout << "Tree doesn't constains \"white\"\n";
  }

  tree.clear();

  std::cout << "rootNodePtr: " << tree.rootNodePtr << '\n';

  std::cout << "Tree:\n";
  tree.print();

  return 0;
}
