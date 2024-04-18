#include "Board.h"

#include <iostream>

Board::Board()
{
    for (int row : {0, 1, 2})
    {
        for (int column : {0, 1, 2})
        {
            tiles[row][column] = ' ';
        }
    }
    prevPlayer = ' ';
    prevMoveNum = 0;
}

bool Board::gameEnded() const
{
    // Check rows for ending condition
    for (int row : {0, 1, 2})
    {
        if (tiles[row][0] != ' ' &&
            tiles[row][0] == tiles[row][1] &&
            tiles[row][1] == tiles[row][2] &&
            tiles[row][0] == tiles[row][2])
        {
            return true;
        }
    }
    // Check columns for ending condition
    for (int column : {0, 1, 2})
    {
        if (tiles[0][column] != ' ' &&
            tiles[0][column] == tiles[1][column] &&
            tiles[1][column] == tiles[2][column] &&
            tiles[0][column] == tiles[2][column])
        {
            return true;
        }
    }
    // Check positive gradient diagonal for ending condition
    if (tiles[0][0] != ' ' &&
        tiles[0][0] == tiles[1][1] &&
        tiles[1][1] == tiles[2][2] &&
        tiles[0][0] == tiles[2][2])
    {
        return true;
    }
    // Check negative gradient diagonal for ending condition
    if (tiles[0][2] != ' ' &&
        tiles[0][2] == tiles[1][1] &&
        tiles[1][1] == tiles[2][0] &&
        tiles[0][2] == tiles[2][0])
    {
        return true;
    }
    // No ending condition met
    return false;
}

bool Board::invalidMove(Move m) const
{
    // "the players must alternate."
    if (m.player == prevPlayer)
    {
        return true;
    }
    // "each move has a number one higher than the previous move."
    if (prevMoveNum + 1 != m.number)
    {
        return true;
    }
    // "Each move must claim an unclaimed square.""
    if (tiles[m.row - 1][m.column - 1] != ' ')
    {
        return true;
    }
    // "If any player claims three squares that form a line horizontally, vertically,
    // or diagonally, that player wins and the game is over; no further moves are
    // allowed."
    if (gameEnded())
    {
        return true;
    }
    // No rules violated
    return false;
}

void Board::printResult() const
{
    if (gameEnded())
    {
        std::cout << "Game over: " << prevPlayer << " wins.\n";
    }
    else
    {
        if (prevMoveNum == 0)
        {
            std::cout << "Game in progress: New game.\n";
        }
        else if (prevMoveNum == 9)
        {
            std::cout << "Game over: Draw.\n";
        }
        else
        {
            if (prevPlayer == 'X')
            {
                std::cout << "Game in progress: O\'s turn.\n";
            }
            else
            {
                std::cout << "Game in progress: X\'s turn.\n";
            }
        }
    }
}
