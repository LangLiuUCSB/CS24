#include "Move.h"

#include <string>
#include <cctype>

Move::Move(const std::string &input)
{
    rawLine = input;
    number = 0;
    player = ' ';
    row = 0;
    column = 0;
}

bool Move::goodFormat() const
{
    if (!std::isdigit(rawLine[0]) || rawLine[0] == '0')
    {
        return false;
    }
    if (!std::isspace(rawLine[1]))
    {
        return false;
    }
    unsigned int i = 2;
    while (std::isspace(rawLine[i]))
    {
        i++;
    }
    if (toupper(rawLine[i]) != 'X' && toupper(rawLine[i]) != 'O')
    {
        return false;
    }
    i++;
    if (!std::isspace(rawLine[i]))
    {
        return false;
    }
    i++;
    while (std::isspace(rawLine[i]))
    {
        i++;
    }
    if (toupper(rawLine[i]) != 'A' && toupper(rawLine[i]) != 'B' && toupper(rawLine[i]) != 'C')
    {
        return false;
    }
    i++;
    if (rawLine[i] != '1' && rawLine[i] != '2' && rawLine[i] != '3')
    {
        return false;
    }
    i++;
    if (rawLine.size() > i)
    {
        if (!std::isspace(rawLine[i]))
        {
            return false;
        }
        i++;
        while (rawLine[i] != '#' && i < rawLine.size())
        {
            if (!std::isspace(rawLine[i]))
            {
                return false;
            }
            i++;
        }
    }
    return true;
};

void Move::parseRawLine()
{
    number = rawLine[0] - '0';
    int i = 2;
    while (std::isspace(rawLine[i]))
    {
        i++;
    }
    player = toupper(rawLine[i]) == 'X' ? 'X' : 'O';
    i += 2;
    while (std::isspace(rawLine[i]))
    {
        i++;
    }
    row = toupper(rawLine[i]) == 'A'   ? 1
          : toupper(rawLine[i]) == 'B' ? 2
                                       : 3;
    column = rawLine[i + 1] - '0';
}

std::string Move::to_string() const
{
    std::string str;
    str += '0' + char(number);
    str += ' ';
    str += player;
    str += ' ';
    str += row == 1   ? 'A'
           : row == 2 ? 'B'
                      : 'C';
    str += '0' + char(column);
    return str;
}
