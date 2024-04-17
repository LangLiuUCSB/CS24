#include "Board.h"
#include "Move.h"
#include <iostream>
#include <map>

bool goodFormat(std::string input)
{
    if (input.size() < 6 || input.size() == 7)
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
    char playerCode = input[2];
    if (playerCode != 'X' && playerCode != 'O' && playerCode != 'x' && playerCode != 'o')
    {
        return false;
    }
    if (!std::isspace(input[3]))
    {
        return false;
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
    if (input.size() > 6 && (!std::isspace(input[6]) || input[7] != '#'))
    {
        return false;
    }
    return true;
}

bool validMove(Move m, Board b)
{
    return false;
}

int main(int argc, char **argv)
{
    Board game;
    std::string line;
    for (std::getline(std::cin, line); line != ""; std::getline(std::cin, line))
    {
        if (goodFormat(line))
        {
            Move move(line);
            if (move.player == game.prevPlayer)
            {
                std::cout << "Invalid move.\n";
                return 2;
            }
            if (game.prevMoveNum + 1 != move.number)
            {
                std::cout << "Invalid move.\n";
                return 2;
            }

            if (game.coor[move.row - 1][move.column - 1] != ' ')
            {
                std::cout << "Invalid move.\n";
                return 2;
            }
            if (game.ended())
            {
                std::cout << "Invalid move.\n";
                return 2;
            }
            game.coor[move.row - 1][move.column - 1] = move.player;
            game.prevPlayer = move.player;
            game.prevMoveNum = move.number;
        }
        else
        {
            std::cout << "Parse error.\n";
            return 1;
        }
    }
    if (game.ended())
    {
        std::cout << "Game over: " << game.prevPlayer << "wins.\n";
    }
    else
    {
        if (game.prevMoveNum == 0)
        {
            std::cout << "Game in progress: New game.\n";
        }
        else if (game.prevMoveNum == 9)
        {
            std::cout << "Game over: Draw.\n";
        }
        else
        {
            if (game.prevPlayer == 'X')
            {
                std::cout << "Game in progress: O\'s turn.\n";
            }
            else
            {
                std::cout << "Game in progress: X\'s turn.\n";
            }
        }
    }
    return 0;
}
