#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

struct Board
{
    // Member Variables
    char tiles[3][3];
    char prevPlayer;
    int prevMoveNum;

    // Constructor
    Board();

    // Check if game has met an ending condition
    bool gameEnded() const;

    // Check validity of a move on the board in its current state
    bool invalidMove(Move m) const;

    // Print game result
    void printResult() const;
};

#endif