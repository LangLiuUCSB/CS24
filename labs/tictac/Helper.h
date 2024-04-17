#ifndef HELPER_H
#define HELPER_H

#include "Board.h"
#include "Move.h"
#include <string>

bool goodFormat(std::string input);
bool validMove(Move m, Board b);

#endif