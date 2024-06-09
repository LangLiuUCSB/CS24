#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "Point.h"
#include "Route.h"

struct Node
{
  short x, y, z;
  unsigned short cost;
  Node *east, *south, *west, *north;
  Node(unsigned short x, unsigned short y, unsigned short z) : x(x), y(y), z(z), east(nullptr), south(nullptr), west(nullptr), north(nullptr) {}
};

class VoxMap
{
  // Member Variables
  unsigned short xLim, yLim, zLim;
  size_t map_area, map_volume;
  Node **graph;

  // Helper Functions
  inline char hexToDec(char hex) const { return (hex <= '9') ? hex - '0' : hex - 'W'; }
  inline bool inBounds2D(short x, short y) const { return 0 <= x && x < xLim && 0 <= y && y < yLim; }
  inline bool inBounds3D(short x, short y, short z) const
  {
    return 0 <= x && x < xLim && 0 <= y && y < yLim && 0 < z && z < zLim;
  }
  Node *getNode(short x, short y, short z) const { return graph[x + xLim * (y + yLim * z)]; };
  Node *setCost(short x, short y, short z, unsigned short cost)
  {
    graph[x + xLim * (y + yLim * z)]->cost = cost;
    return graph[x + xLim * (y + yLim * z)];
  };

public:
  VoxMap(std::istream &stream);
  ~VoxMap();

  Route route(Point src, Point dst);

  void printMap(Point src, Point dst) const;
};

#endif
