#include "VoxMap.h"
#include "Errors.h"

#include <iomanip>
#include <stdexcept>

static const unsigned char hexToDec[103] = {
    ['0'] = 0,
    ['1'] = 1,
    ['2'] = 2,
    ['3'] = 3,
    ['4'] = 4,
    ['5'] = 5,
    ['6'] = 6,
    ['7'] = 7,
    ['8'] = 8,
    ['9'] = 9,
    ['a'] = 10,
    ['b'] = 11,
    ['c'] = 12,
    ['d'] = 13,
    ['e'] = 14,
    ['f'] = 15};

VoxMap::VoxMap(std::istream &stream)
{
  stream >> xWidth >> yDepth >> zHeight;
  map = new bool **[zHeight];
  std::string xLine;
  unsigned char hex, dec;
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

  // Bird's Eye 2D Manhattan Distance from Destination
  auto getCost = [dst](Point p) -> unsigned short
  { return (p.x < dst.x ? dst.x - p.x : p.x - dst.x) + (p.y < dst.y ? dst.y - p.y : p.y - dst.y); };

  // Find Route
  Route moves;
  PathNode *start = new PathNode(src, getCost(src), nullptr, Move::EAST);

  std::unordered_set<Point, PointHash> discovered = {src};

  auto compare = [](const PathNode *n1, const PathNode *n2)
  { return n1->cost > n2->cost; };
  std::priority_queue<PathNode *, std::vector<PathNode *>, decltype(compare)> frontiers(compare);

  /*
  auto discover = [this, &discovered, &frontiers, getCost](Move direction, PathNode *currNode)
  {
    Point p = currNode->point;
    switch (direction)
    {
    case Move::EAST:
      ++p.x;
      break;
    case Move::SOUTH:
      ++p.y;
      break;
    case Move::WEST:
      --p.x;
      break;
    case Move::NORTH:
      --p.y;
      break;
    }
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      discovered.insert(p);
      frontiers.push(new PathNode(p, getCost(p), currNode, direction));
    }
  };
  */

  auto discoverV2 = [this, &discovered, &frontiers, getCost](PathNode *currNode)
  {
    Point p = currNode->point;
    // East
    ++p.x;
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      discovered.insert(p);
      frontiers.push(new PathNode(p, getCost(p), currNode, Move::EAST));
    }
    // South
    --p.x;
    ++p.y;
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      discovered.insert(p);
      frontiers.push(new PathNode(p, getCost(p), currNode, Move::SOUTH));
    }
    // West
    --p.x;
    --p.y;
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      discovered.insert(p);
      frontiers.push(new PathNode(p, getCost(p), currNode, Move::WEST));
    }
    // North
    ++p.x;
    --p.y;
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      discovered.insert(p);
      frontiers.push(new PathNode(p, getCost(p), currNode, Move::NORTH));
    }
  };

  PathNode *currNode = start;
  std::cout << "(" << std::setfill('0') << std::setw(2) << currNode->point.x;
  std::cout << "," << std::setfill('0') << std::setw(2) << currNode->point.y;
  std::cout << "," << std::setfill('0') << std::setw(2) << currNode->point.z;
  unsigned short i = 0;

  discoverV2(currNode);
  currNode = frontiers.top();
  frontiers.pop();
  if (currNode->point == dst)
  {
    std::cout << ")\nFound on turn " << i << "\npritority queue has " << frontiers.size();
  }
  ++i;

  while (!frontiers.empty())
  {
    discoverV2(currNode);
    currNode = frontiers.top();
    frontiers.pop();
    // std::cout << ")~(" << std::setfill('0') << std::setw(2) << currNode->point.x;
    // std::cout << "," << std::setfill('0') << std::setw(2) << currNode->point.y;
    // std::cout << "," << std::setfill('0') << std::setw(2) << currNode->point.z;
    if (currNode->point == dst)
    {
      // std::cout << ")\nFound on turn " << i << "\nPritority Queue has " << frontiers.size() << " Frontiers left\n";
      while (currNode->back)
      {
        moves.insert(moves.begin(), currNode->move);
        currNode = currNode->back;
      }
      return moves;
    }
    ++i;
  }
  std::cout << "\n";

  // No Route
  throw NoRoute(src, dst);
}

static const std::string tickLabel = "0123456789abcdefghijklmnopqrstuvwxyz";

void VoxMap::printMap() const
{
  std::cout << " " << tickLabel << "\n";
  for (unsigned short z = 1; z < zHeight; z++)
  {
    for (unsigned short y = 0; y < yDepth; y++)
    {
      std::cout << ((y < 36) ? tickLabel[y] : ' ');
      for (unsigned short x = 0; x < xWidth; x++)
      {
        std::cout << (map[z][y][x] ? "#" : " ");
      }
      std::cout << "\n";
    }
    std::cout << " " << tickLabel << "\n";
  }
}
