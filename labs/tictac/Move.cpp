#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.
Move::Move(const std::string &input)
{
    number = static_cast<int>(input[0]);
    player = input[2] == 'X' || input[2] == 'x' ? 'X' : 'O';
    row = input[4] == 'A' || input[4] == 'a'   ? 1
          : input[4] == 'B' || input[4] == 'b' ? 2
                                               : 3;
    column = static_cast<int>(input[5]);
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