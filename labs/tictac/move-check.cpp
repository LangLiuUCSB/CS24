#include "Errors.h"
#include "Move.h"
#include "Helper.h"

#include <iostream>

#include "Helper.cpp"

int main(int argc, char **argv)
{
  bool verbose = false;

  if (argc == 2 && std::string(argv[1]) == "-v")
  {
    verbose = true;
  }

  if (verbose)
  {
    std::cout << "> ";
  }

  std::string line;
  std::getline(std::cin, line);

  try
  {
    if (goodFormat(line))
    {
      Move move(line);
      std::cout << move.to_string() << '\n';
      return 0;
    }
    else
    {
      std::cout << "Parse error.\n";
      return 1;
    }
  }
  catch (const ParseError &e)
  {
    if (verbose)
    {
      std::cout << "Parse error: " << e.what() << '\n';
    }
    else
    {
      std::cout << "Parse error.\n";
    }

    return 1;
  }
}
