#include "Move.h"

#include <iostream>

int main()
{
  std::string line;
  std::getline(std::cin, line);
  Move move(line);
  if (move.goodFormat())
  {
    move.parseRawLine();
    std::cout << move.to_string() << '\n';
    return 0;
  }
  else
  {
    std::cout << "Parse error.\n";
    return 1;
  }
}
