#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <vector>
#include <queue>
#include <bitset>

#include "Point.h"
#include "Route.h"

struct Node
{
  short x, y, z;
  unsigned short cost;
  Node *east, *south, *west, *north;
  Node(unsigned short x, unsigned short y, unsigned short z) : x(x), y(y), z(z) {}
};

class VoxMap
{
  // Member Variables
  unsigned short xLim, yLim, zLim;
  size_t map_area, map_size;
  Node **graph;

  // Helper Functions
  inline char hexToDec(char hex) const { return (hex <= '9') ? hex - '0' : hex - 'W'; }

public:
  VoxMap(std::istream &stream);
  ~VoxMap();

  Route route(Point src, Point dst);

  void printMap(Point src, Point dst) const;
};

#endif
