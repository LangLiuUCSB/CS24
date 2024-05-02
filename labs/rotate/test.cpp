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
  tree.insert("indigo");
  tree.insert("violet");

  for (size_t i = 0; i < 7; i++)
  {
    std::cout << tree.find(tree.lookup(i)) << ": " << tree.lookup(i) << '\n';
  }
  std::cout << tree.find("white") << ": white\n";
  std::cout << tree.contains("white") << '\n';

  tree.print();

  tree.clear();

  std::cout << tree.rootNodePtr << '\n';

  return 0;
}
