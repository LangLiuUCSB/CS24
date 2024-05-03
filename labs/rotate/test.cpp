#include "Tree.h"
#include <iostream>

int main()
{
  Tree tree;

  std::string roygbiv[] = {"red", "orange", "yellow", "green", "blue", "indigo", "violet"};

  for (std::string color : roygbiv)
  {
    tree.insert(color);
  }

  std::cout << "rootNodePtr: " << tree.rootNodePtr << "->" << tree.rootNodePtr->data << '\n';

  std::cout << "Tree: ";
  tree.print();

  for (std::string color : roygbiv)
  {
    std::cout << tree.find(color) << ": " << color << '\n';
  }
  /*
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

  std::cout << "Tree: ";
  tree.print();
  */

  return 0;
}
