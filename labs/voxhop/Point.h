#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
  short x, y, z;
  unsigned short cost;

  Point() {}
  Point(short x, short y, short z) : x(x), y(y), z(z) {}
  Point(short x, short y, short z, unsigned short cost) : x(x), y(y), z(z), cost(cost) {}

  bool operator==(const Point &other) const { return other.x == x && other.y == y && other.z == z; }
  bool operator!=(const Point &other) const { return other.x != x || other.y != y || other.z != z; }
};

std::istream &operator>>(std::istream &stream, Point &point);
std::ostream &operator<<(std::ostream &stream, const Point &point);

#endif
