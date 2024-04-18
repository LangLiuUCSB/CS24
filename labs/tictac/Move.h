#ifndef MOVE_H
#define MOVE_H

#include <string>

struct Move
{
  // Member Variables
  std::string rawLine;
  int number;
  char player;
  int row;
  int column;

  // Constructor
  Move(const std::string &input);

  // Check if input line has good format
  bool goodFormat() const;

  // Parse raw line into move information
  void parseRawLine();

  // Render a Move as text
  std::string to_string() const;
};

#endif
