#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <vector>
#include <queue>

#include "Point.h"
#include "Route.h"
/*
00000000 unscanned (Empty, because Fulls are scanned by default)
01000000 scanned   Full unclimbable
01100000 scanned   Full climbable

100XXXXX scanned   Empty EAST
101XXXXX scanned   Empty WEST
110XXXXX scanned   Empty SOUTH
111XXXXX scanned   Empty NORTH
1XX00000 scanned   Empty X     0fall
1XX00001 scanned   Empty X     1fall
...
1XX01111 scanned   Empty X     30fall
1XX11111 scanned   Empty X     >30fall

possibly max 62 fall and min 0 fall
*/
class VoxMap
{
  // Member Variables
  bool ***map; // map[z][y][x]
  unsigned short xWidth;
  unsigned short yDepth;
  unsigned short zHeight;

  // Helper Functions
  bool inBounds3D(Point p) { return 0 <= p.x && p.x < xWidth && 0 <= p.y && p.y < yDepth && 0 < p.z && p.z < zHeight; }
  bool isEmpty(Point p) { return !map[p.z][p.y][p.x]; }
  bool inBounds2D(Point p) { return 0 <= p.x && p.x < xWidth && 0 <= p.y && p.y < yDepth; }

public:
  VoxMap(std::istream &stream);
  ~VoxMap();

  Route route(Point src, Point dst);
};

#endif
