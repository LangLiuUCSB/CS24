#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.
Move::Move(const std::string &input)
{
    int i = 0;
    while (std::isspace(input[i]))
    {
        i++;
    }
    number = static_cast<int>(input[i]);
    i += 2;
    while (std::isspace(input[i]))
    {
        i++;
    }
    player = input[i] == 'X' || input[i] == 'x' ? 'X' : 'O';
    i += 2;
    while (std::isspace(input[i]))
    {
        i++;
    }
    row = input[i] == 'A' || input[i] == 'a'   ? 1
          : input[i] == 'B' || input[i] == 'b' ? 2
                                               : 3;
    column = static_cast<int>(input[i + 1]);
}

std::string Move::to_string() const
{
    std::string str;
    str += char(number);
    str += ' ';
    str += player;
    str += ' ';
    str += row == 1   ? 'A'
           : row == 2 ? 'B'
                      : 'C';
    str += char(column);
    return str;
}