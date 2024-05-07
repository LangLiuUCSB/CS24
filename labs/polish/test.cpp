#include "AST.h"
#include <iostream>

int main()
{
  std::string line = "2 6 -";
  AST *ast = AST::parse(line);
  std::cout << ast << " -> ast -> \"" << line << "\" -> " << ast->value() << "\n";
  delete ast;

  return 0;
}
