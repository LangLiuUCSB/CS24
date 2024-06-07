#include "VoxMap.h"
#include "Errors.h"

#include <cstdlib>
#include <algorithm>
#include <stdexcept>

VoxMap::VoxMap(std::istream &stream)
{
  stream >> xWidth >> yDepth >> zHeight;

  map = new bool[xWidth * yDepth * zHeight];

  for (unsigned short z = 0; z < zHeight; z++)
  {
    for (unsigned short y = 0; y < yDepth; y++)
    {
      std::string xLine;
      stream >> xLine;

      for (unsigned short xQuad = 0; xQuad < xWidth; xQuad += 4)
      {
        unsigned char hex = xLine[xQuad / 4];
        unsigned char dec = hexToDec(hex);

        // Calculate the base index in the flat vector
        size_t baseIndex = (z * yDepth * xWidth) + (y * xWidth) + xQuad;

        map[baseIndex] = (dec & 0b1000) >> 3;
        map[baseIndex + 1] = (dec & 0b0100) >> 2;
        map[baseIndex + 2] = (dec & 0b0010) >> 1;
        map[baseIndex + 3] = dec & 0b0001;
      }
    }
  }
}

VoxMap::~VoxMap()
{
  delete[] map;
}

Route VoxMap::route(Point src, Point dst)
{
  if (!inBounds3D(src) || !isEmpty(src) || isEmpty(src + Point(0, 0, -1)))
    throw InvalidPoint(src);
  if (!inBounds3D(dst) || !isEmpty(dst) || isEmpty(dst + Point(0, 0, -1)))
    throw InvalidPoint(dst);

  Route path;

  auto getCost = [dst](Point p) -> unsigned short // Manhattan Distance from Destination
  { return abs(p.x - dst.x) + abs(p.y - dst.y) + abs(p.z - dst.z); };

  auto compare = [](const Point &a, const Point &b)
  { return a.cost > b.cost; };
  std::priority_queue<Point, std::vector<Point>, decltype(compare)> frontiers(compare);
  src.cost = getCost(src);
  frontiers.push(src);

  std::vector<std::vector<std::vector<bool>>> scanned(zHeight, std::vector<std::vector<bool>>(yDepth, std::vector<bool>(xWidth, false)));
  scanned[src.z][src.y][src.x] = true;

  std::vector<std::vector<std::vector<Point>>> prevPoint(zHeight, std::vector<std::vector<Point>>(yDepth, std::vector<Point>(xWidth)));

  std::vector<std::vector<std::vector<Move>>> prevMove(zHeight, std::vector<std::vector<Move>>(yDepth, std::vector<Move>(xWidth)));

  Point currPoint;
  while (!frontiers.empty())
  {
    currPoint = frontiers.top();
    frontiers.pop();

    if (currPoint == dst)
    {
      while (currPoint != src)
      {
        path.push_back(prevMove[currPoint.z][currPoint.y][currPoint.x]);
        currPoint = prevPoint[currPoint.z][currPoint.y][currPoint.x];
      }
      std::reverse(path.begin(), path.end());
      return path;
    }
    Point newPoint;
    Point displacement[] = {Point(1, 0, 0), Point(0, 1, 0), Point(-1, 0, 0), Point(0, -1, 0)};
    for (Move direction : {Move::EAST, Move::SOUTH, Move::WEST, Move::NORTH})
    {
      newPoint = currPoint + displacement[direction];
      if (inBounds2D(newPoint))
      {
        if (isEmpty(newPoint))
        {
          // fall until below is full
          --newPoint.z;
          while (0 < newPoint.z)
          {
            if (!isEmpty(newPoint))
              break;
            --newPoint.z;
          }
          ++newPoint.z;
          if (!scanned[newPoint.z][newPoint.y][newPoint.x] && !isEmpty(newPoint + Point(0, 0, -1)))
          {
            newPoint.cost = getCost(newPoint);
            frontiers.push(newPoint);
            prevPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;
            prevMove[newPoint.z][newPoint.y][newPoint.x] = direction;

            scanned[newPoint.z][newPoint.y][newPoint.x] = true;
            ++newPoint.z;
            while (newPoint.z < zHeight)
            {
              if (!isEmpty(newPoint))
                break;
              scanned[newPoint.z][newPoint.y][newPoint.x] = true;
              ++newPoint.z;
            }
          }
        }
        else // full
        {
          if (currPoint.z + 1 < zHeight && isEmpty(currPoint + Point(0, 0, 1))) // Empty above current
          {
            ++newPoint.z;
            if (!scanned[newPoint.z][newPoint.y][newPoint.x] && isEmpty(newPoint)) // empty above full
            {
              newPoint.cost = getCost(newPoint);
              frontiers.push(newPoint);
              scanned[newPoint.z][newPoint.y][newPoint.x] = true;
              prevPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;
              prevMove[newPoint.z][newPoint.y][newPoint.x] = direction;
            }
          }
        }
      }
    }
  }
  throw NoRoute(src, dst);
}
/*
for (unsigned short z = 5; z < zHeight; z++)
{
  std::cout << z << "\n";
  for (unsigned short y = 0; y < yDepth; y++)
  {
    for (unsigned short x = 0; x < xWidth; x++)
    {
      std::cout << prevPoint[z][y][x];
    }
    std::cout << "\n";
  }
}
*/
