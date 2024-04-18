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

    // Helper to check if game has met an ending condition.
    bool ended() const;

    // Helper to check if a valid move have been made on current state of the Board.
    bool validMove(Move m) const;
};

#endif