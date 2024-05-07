#include "AST.h"
#include <iostream>

int main()
{
  std::string line = "37.5 883.6 - -12.2 611.4 - -469.6 % % 47.4 814 -295.7 - ~ % +";
  AST *ast = AST::parse(line);
  std::cout << ast << " -> ast -> \"" << line << "\" -> " << ast->value() << "\n";
  std::cout << ast->prefix() << "\n";
  delete ast;

  return 0;
}
