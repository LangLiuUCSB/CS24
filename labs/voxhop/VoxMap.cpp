#include "VoxMap.h"
#include "Errors.h"

#include <algorithm>
#include <stdexcept>

VoxMap::VoxMap(std::istream &stream)
{
  stream >> xWidth >> yDepth >> zHeight;
  map = new bool **[zHeight];
  std::string xLine;
  unsigned char hex, dec;
  unsigned char hexToDec[103];
  hexToDec[48] = 0;
  hexToDec[49] = 1;
  hexToDec[50] = 2;
  hexToDec[51] = 3;
  hexToDec[52] = 4;
  hexToDec[53] = 5;
  hexToDec[54] = 6;
  hexToDec[55] = 7;
  hexToDec[56] = 8;
  hexToDec[57] = 9;
  hexToDec[97] = 10;
  hexToDec[98] = 11;
  hexToDec[99] = 12;
  hexToDec[100] = 13;
  hexToDec[101] = 14;
  hexToDec[102] = 15;
  for (unsigned short z = 0; z < zHeight; z++)
  {
    map[z] = new bool *[yDepth];
    for (unsigned short y = 0; y < yDepth; y++)
    {
      map[z][y] = new bool[xWidth];
      stream >> xLine;
      for (unsigned short xQuad = 0; xQuad < xWidth; xQuad += 4)
      {
        hex = xLine[xQuad / 4];
        if ((map[z][y][xQuad] = (dec = hexToDec[hex]) / 8))
          dec %= 8;
        if ((map[z][y][xQuad + 1] = dec / 4))
          dec %= 4;
        if ((map[z][y][xQuad + 2] = dec / 2))
          map[z][y][xQuad + 3] = dec % 2;
        else
          map[z][y][xQuad + 3] = dec;
      }
    }
  }
}

VoxMap::~VoxMap()
{
  for (unsigned short z = 0; z < zHeight; z++)
  {
    for (unsigned short y = 0; y < yDepth; y++)
    {
      delete[] map[z][y];
    }
    delete[] map[z];
  }
  delete[] map;
}

Route VoxMap::route(Point src, Point dst)
{
  if (!inBounds3D(src) || !isEmpty(src) || isEmpty(src + Point(0, 0, -1)))
    throw InvalidPoint(src);
  if (!inBounds3D(dst) || !isEmpty(dst) || isEmpty(dst + Point(0, 0, -1)))
    throw InvalidPoint(dst);

  Route path;
  if (src == dst)
    return path;

  auto getCost = [dst](Point p) -> unsigned short // Manhattan Distance from Destination
  { return (p.x < dst.x ? dst.x - p.x : p.x - dst.x) + (p.y < dst.y ? dst.y - p.y : p.y - dst.y) + (p.z < dst.z ? dst.z - p.z : p.z - dst.z); };

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
      // for (unsigned short turn = 0; turn < 9; turn++)
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
      if (inBounds3D(newPoint))
      {
        if (isEmpty(newPoint))
        {
          // fall until below is full
          --newPoint.z;
          while (inBounds3D(newPoint))
          {
            if (!isEmpty(newPoint))
              break;
            --newPoint.z;
          }
          ++newPoint.z;
          if (!scanned[newPoint.z][newPoint.y][newPoint.x])
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
          if (inBounds3D(currPoint + Point(0, 0, 1)) && isEmpty(currPoint + Point(0, 0, 1))) // Empty above current
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
