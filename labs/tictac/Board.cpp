#include "Errors.h"
#include "Board.h"

// Space for implementing Board functions.

Board::Board()
{
    for (int row : {1, 2, 3})
    {
        for (int column : {1, 2, 3})
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
    for (int row : {1, 2, 3})
    {
        if (coor[row][1] != ' ' &&
            coor[row][1] == coor[row][2] &&
            coor[row][2] == coor[row][3] &&
            coor[row][1] == coor[row][3])
        {
            return true;
        }
    }
    // Check columns for ending condition
    for (int column : {1, 2, 3})
    {
        if (coor[1][column] != ' ' &&
            coor[1][column] == coor[2][column] &&
            coor[2][column] == coor[3][column] &&
            coor[1][column] == coor[3][column])
        {
            return true;
        }
    }
    // Checks positive gradient diagonal for ending condition
    if (coor[1][1] != ' ' &&
        coor[1][1] == coor[2][2] &&
        coor[2][2] == coor[3][3] &&
        coor[1][1] == coor[3][3])
    {
        return true;
    }
    // Checks negative gradient diagonal for ending condition
    if (coor[1][3] != ' ' &&
        coor[1][3] == coor[2][2] &&
        coor[2][2] == coor[3][1] &&
        coor[1][3] == coor[3][1])
    {
        return true;
    }
    return false;
}