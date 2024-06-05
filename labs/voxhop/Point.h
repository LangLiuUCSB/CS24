#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
  int x;
  int y;
  int z;

  Point() {}
  Point(int x, int y, int z) : x(x), y(y), z(z) {}

  bool operator==(const Point &other) const { return other.x == x && other.y == y && other.z == z; }
};

struct PointHash
{
  std::size_t operator()(const Point &p) const { return ((17 * 31 + std::hash<int>{}(p.x)) * 31 + std::hash<int>{}(p.y)) * 31 + std::hash<int>{}(p.z); }
};

std::istream &operator>>(std::istream &stream, Point &point);
std::ostream &operator<<(std::ostream &stream, const Point &point);

#endif
