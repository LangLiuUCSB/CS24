#include "Route.h"

std::ostream &operator<<(std::ostream &stream, Move move)
{
  switch (move)
  {
  case Move::EAST:
    return stream << 'e';
    break;
  case Move::SOUTH:
    return stream << 's';
    break;
  case Move::WEST:
    return stream << 'w';
    break;
  default:
    return stream << 'n';
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const Route &route)
{
  for (auto it = route.rbegin(); it != route.rend(); ++it)
    stream << *it;
  return stream;
}
