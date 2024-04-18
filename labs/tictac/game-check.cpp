#include "Board.h"
#include "Move.h"

#include <iostream>

int main()
{
    Board board;
    std::string currLine;
    for (std::getline(std::cin, currLine); currLine != ""; std::getline(std::cin, currLine))
    {
        Move currMove(currLine);
        if (currMove.goodFormat())
        {
            currMove.parseRawLine();
            if (board.invalidMove(currMove))
            {
                std::cout << "Invalid move.\n";
                return 2;
            }
            board.tiles[currMove.row - 1][currMove.column - 1] = currMove.player;
            board.prevPlayer = currMove.player;
            board.prevMoveNum = currMove.number;
        }
        else
        {
            std::cout << "Parse error.\n";
            return 1;
        }
    }
    board.printResult();
    return 0;
}
