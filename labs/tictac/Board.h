#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

struct Board
{
    // Member Variables
    char coor[3][3];
    char prevPlayer;
    int prevMoveNum;

    // The constructor
    Board();

    // Helper to check is game has met an ending condition.
    bool ended() const;
};

#endif