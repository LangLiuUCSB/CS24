#include "Errors.h"
#include "Move.h"

#include <iostream>
#include <cctype>

bool goodFormat(std::string input)
{
  if (input.size() < 6 || input.size() == 7)
  {
    return false;
  }
  while (std::isspace(input[0]))
  {
    input.erase(input.begin());
  }
  char moveNum = input[0];
  if (moveNum > '9' || moveNum < '1')
  {
    return false;
  }
  if (!std::isspace(input[1]))
  {
    return false;
  }
  while (std::isspace(input[2]))
  {
    input.erase(input.begin() + 2);
  }
  char playerCode = input[2];
  if (!isalpha(playerCode))
  {
    return false;
  }
  if (!std::isspace(input[3]))
  {
    return false;
  }
  while (std::isspace(input[4]))
  {
    input.erase(input.begin() + 4);
  }
  char row = input[4];
  if (!isalpha(row))
  {
    return false;
  }
  char column = input[5];
  if (column > '3' || column < '1')
  {
    return false;
  }
  if (input.size() > 6 && input[6] == '#')
  {
    return false;
  }
  for (unsigned int i = 7; input[i] != '#' && i < input.size(); i++)
  {
    if (!std::isspace(input[i]))
    {
      return false;
    }
  }
  return true;
}

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
