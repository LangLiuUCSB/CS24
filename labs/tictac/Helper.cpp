#include "Board.h"
#include "Move.h"
#include "Helper.h"
#include <string>
#include <cctype>

bool goodFormat(std::string input)
{
    if (input.size() < 6)
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
};

bool validMove(Move m, Board b)
{
    if (m.player == b.prevPlayer)
    {
        return false;
    }
    if (b.prevMoveNum + 1 != m.number)
    {
        return false;
    }
    if (b.coor[m.row - 1][m.column - 1] != ' ')
    {
        return false;
    }
    if (b.ended())
    {
        return false;
    }
    return true;
}