#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <vector>
#include <unordered_set>
#include <queue>

#include "Point.h"
#include "Route.h"

class VoxMap
{
  // Member Variables
  bool ***map; // map[z][y][x]
  unsigned short xWidth;
  unsigned short yDepth;
  unsigned short zHeight;

  // Helper Functions
  bool inBounds(Point p) { return 0 <= p.x && p.x < xWidth && 0 <= p.y && p.y < yDepth && 0 < p.z && p.z < zHeight; }
  bool isEmpty(Point p) { return !map[p.z][p.y][p.x]; }
  bool onFull(Point p) { return map[p.z - 1][p.y][p.x]; }

public:
  // Constructor & Destructor
  VoxMap(std::istream &stream);
  ~VoxMap();

  // Find a Route if reachable
  Route route(Point src, Point dst);

  // Extra Functions
  void printMap() const;
};

#endif
