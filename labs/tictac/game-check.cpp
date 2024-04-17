#include "Board.h"
#include "Move.h"
#include "Helper.h"
#include <iostream>

int main(int argc, char **argv)
{
    Board game;
    std::string line;
    for (std::getline(std::cin, line); line != ""; std::getline(std::cin, line))
    {
        if (goodFormat(line))
        {
            Move move(line);
            if (!validMove(move, game))
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
