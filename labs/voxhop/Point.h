#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
  short x, y, z;

  Point() {}
  Point(short x, short y, short z) : x(x), y(y), z(z) {}
};

std::istream &operator>>(std::istream &stream, Point &point);
std::ostream &operator<<(std::ostream &stream, const Point &point);

#endif
