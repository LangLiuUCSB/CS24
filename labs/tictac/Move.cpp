#include "Errors.h"
#include "Move.h"
#include <string>
#include <cctype>

// Space for implementing Move functions.
Move::Move(const std::string &input)
{
    raw = input;
    number = 0;
    player = ' ';
    row = 0;
    column = 0;
}

bool Move::goodFormat() const
{
    if (!std::isdigit(raw[0]) || raw[0] == '0')
    {
        return false;
    }
    if (!std::isspace(raw[1]))
    {
        return false;
    }
    unsigned int i = 2;
    while (std::isspace(raw[i]))
    {
        i++;
    }
    if (toupper(raw[i]) != 'X' && toupper(raw[i]) != 'O')
    {
        return false;
    }
    i++;
    if (!std::isspace(raw[i]))
    {
        return false;
    }
    i++;
    while (std::isspace(raw[i]))
    {
        i++;
    }
    if (toupper(raw[i]) != 'A' && toupper(raw[i]) != 'B' && toupper(raw[i]) != 'C')
    {
        return false;
    }
    i++;
    if (raw[i] != '1' && raw[i] != '2' && raw[i] != '3')
    {
        return false;
    }
    i++;
    if (raw.size() > i)
    {
        if (!std::isspace(raw[i]))
        {
            return false;
        }
        i++;
        while (raw[i] != '#')
        {
            if (!std::isspace(raw[i]))
            {
                return false;
            }
            i++;
        }
    }
    return true;
};

void Move::update()
{
    number = static_cast<int>(raw[0]);
    int i = 2;
    while (std::isspace(raw[i]))
    {
        i++;
    }
    player = raw[i] == 'X' || raw[i] == 'x' ? 'X' : 'O';
    i += 2;
    while (std::isspace(raw[i]))
    {
        i++;
    }
    row = raw[i] == 'A' || raw[i] == 'a'   ? 1
          : raw[i] == 'B' || raw[i] == 'b' ? 2
                                           : 3;
    column = static_cast<int>(raw[i + 1]);
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

/*
    std::string input = raw;
    if (raw.size() < 6)
    {
        return false;
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
    if (playerCode != 'X' && playerCode != 'O' && playerCode != 'x' && playerCode != 'o')
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
    if (row != 'A' && row != 'B' && row != 'C' && row != 'a' && row != 'b' && row != 'c')
    {
        return false;
    }
    char column = input[5];
    if (column > '3' || column < '1')
    {
        return false;
    }
    if (input.size() > 6 && !std::isspace(input[6]))
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
    */