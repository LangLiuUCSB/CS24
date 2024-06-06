#include "VoxMap.h"
#include "Errors.h"

#include <iomanip>
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
  // Invalid Point
  if (!inBounds(src) || !isEmpty(src) || !onFull(src))
    throw InvalidPoint(src);
  if (!inBounds(dst) || !isEmpty(dst) || !onFull(dst))
    throw InvalidPoint(dst);

  // Find Route
  Route path;
  if (src == dst)
  {
    return path;
  }

  // Bird's Eye 2D Manhattan Distance from Destination
  auto getCost = [dst](Point p) -> unsigned short
  { return (p.x < dst.x ? dst.x - p.x : p.x - dst.x) + (p.y < dst.y ? dst.y - p.y : p.y - dst.y); };

  // Frontiers Priority Queue
  auto compare = [](const Point &a, const Point &b)
  { return a.cost > b.cost; };
  std::priority_queue<Point, std::vector<Point>, decltype(compare)> frontiers(compare);
  src.cost = getCost(src);
  frontiers.push(src);

  // Visited Points Map
  std::vector<std::vector<std::vector<bool>>> visited(zHeight, std::vector<std::vector<bool>>(yDepth, std::vector<bool>(xWidth, false)));
  visited[src.z][src.y][src.x] = true;
  // Previous Point Map
  std::vector<std::vector<std::vector<Point>>> nextPoint(zHeight, std::vector<std::vector<Point>>(yDepth, std::vector<Point>(xWidth)));
  // Previous Move Map
  std::vector<std::vector<std::vector<Move>>> nextMove(zHeight, std::vector<std::vector<Move>>(yDepth, std::vector<Move>(xWidth)));

  Point currPoint;
  while (!frontiers.empty())
  {
    currPoint = frontiers.top();
    frontiers.pop();

    if (currPoint == dst)
    {
      while (currPoint != src)
      {
        path.push_back(nextMove[currPoint.z][currPoint.y][currPoint.x]);
        currPoint = nextPoint[currPoint.z][currPoint.y][currPoint.x];
      }
      std::reverse(path.begin(), path.end());
      return path;
    }
    Point newPoint = currPoint;
    ++newPoint.x; // East
    if (inBounds(newPoint) && isEmpty(newPoint) && !visited[newPoint.z][newPoint.y][newPoint.x])
    {
      visited[newPoint.z][newPoint.y][newPoint.x] = true;
      nextPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;
      nextMove[newPoint.z][newPoint.y][newPoint.x] = Move::EAST;
      newPoint.cost = getCost(newPoint);
      frontiers.push(newPoint);
    }
    newPoint.x -= 2; // West
    if (inBounds(newPoint) && isEmpty(newPoint) && !visited[newPoint.z][newPoint.y][newPoint.x])
    {
      visited[newPoint.z][newPoint.y][newPoint.x] = true;
      nextPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;
      nextMove[newPoint.z][newPoint.y][newPoint.x] = Move::WEST;
      newPoint.cost = getCost(newPoint);
      frontiers.push(newPoint);
    }
    ++newPoint.x;
    ++newPoint.y; // South
    if (inBounds(newPoint) && isEmpty(newPoint) && !visited[newPoint.z][newPoint.y][newPoint.x])
    {
      visited[newPoint.z][newPoint.y][newPoint.x] = true;
      nextPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;
      nextMove[newPoint.z][newPoint.y][newPoint.x] = Move::SOUTH;
      newPoint.cost = getCost(newPoint);
      frontiers.push(newPoint);
    }
    newPoint.y -= 2; // NORTH
    if (inBounds(newPoint) && isEmpty(newPoint) && !visited[newPoint.z][newPoint.y][newPoint.x])
    {
      visited[newPoint.z][newPoint.y][newPoint.x] = true;
      nextPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;
      nextMove[newPoint.z][newPoint.y][newPoint.x] = Move::NORTH;
      newPoint.cost = getCost(newPoint);
      frontiers.push(newPoint);
    }
  }

  // No Route
  throw NoRoute(src, dst);
}

void VoxMap::printMap() const
{
  for (unsigned short z = 1; z < zHeight; z++)
  {
    for (unsigned short y = 0; y < yDepth; y++)
    {
      for (unsigned short x = 0; x < xWidth; x++)
      {
        std::cout << (map[z][y][x] ? "#" : " ");
      }
      std::cout << "\n";
    }
  }
}
