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

    // Helper to check if game has met an ending condition.
    bool gameEnded() const;

    // Helper to check validity of a move on the board in its current state.
    bool invalidMove(Move m) const;

    void printResult() const;
};

#endif