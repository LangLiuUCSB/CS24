#include "Errors.h"
#include "Board.h"

// Space for implementing Board functions.

Board::Board()
{
    for (int row : {0, 1, 2})
    {
        for (int column : {0, 1, 2})
        {
            coor[row][column] = ' ';
        }
    }
    prevPlayer = ' ';
    prevMoveNum = 0;
}

bool Board::ended() const
{
    // Check rows for ending condition
    for (int row : {0, 1, 2})
    {
        if (coor[row][0] != ' ' &&
            coor[row][0] == coor[row][1] &&
            coor[row][1] == coor[row][2] &&
            coor[row][0] == coor[row][2])
        {
            return true;
        }
    }
    // Check columns for ending condition
    for (int column : {0, 1, 2})
    {
        if (coor[0][column] != ' ' &&
            coor[0][column] == coor[1][column] &&
            coor[1][column] == coor[2][column] &&
            coor[0][column] == coor[2][column])
        {
            return true;
        }
    }
    // Checks positive gradient diagonal for ending condition
    if (coor[0][0] != ' ' &&
        coor[0][0] == coor[1][1] &&
        coor[1][1] == coor[2][2] &&
        coor[0][0] == coor[2][2])
    {
        return true;
    }
    // Checks negative gradient diagonal for ending condition
    if (coor[0][2] != ' ' &&
        coor[0][2] == coor[1][1] &&
        coor[1][1] == coor[2][0] &&
        coor[0][2] == coor[2][0])
    {
        return true;
    }
    return false;
}