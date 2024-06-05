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
  Route moves;
  if (src == dst)
  {
    return moves;
  }

  // Bird's Eye 2D Manhattan Distance from Destination
  auto getCost = [dst](Point p) -> unsigned short
  { return (p.x < dst.x ? dst.x - p.x : p.x - dst.x) + (p.y < dst.y ? dst.y - p.y : p.y - dst.y); };

  // Path Start
  PathNode *start = new PathNode(src, getCost(src), nullptr, Move::EAST);

  // Discovered Points
  std::unordered_set<PathNode *> visited = {start};
  std::unordered_set<Point, PointHash> discovered = {src};

  // Frontiers Priority Queue
  auto compare = [](const PathNode *n1, const PathNode *n2)
  { return n1->cost > n2->cost; };
  std::priority_queue<PathNode *, std::vector<PathNode *>, decltype(compare)> frontiers(compare);

  // Adds Valid Frontiers to Priority Queue
  auto discover = [this, &visited, &discovered, &frontiers, getCost](PathNode *currNode)
  {
    Point p = currNode->point;
    ++p.x; // East
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      PathNode *newNode = new PathNode(p, getCost(p), currNode, Move::EAST);
      visited.insert(newNode);
      discovered.insert(p);
      frontiers.push(newNode);
    }
    --p.x;
    ++p.y; // South
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      PathNode *newNode = new PathNode(p, getCost(p), currNode, Move::SOUTH);
      visited.insert(newNode);
      discovered.insert(p);
      frontiers.push(newNode);
    }
    --p.x;
    --p.y; // West
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      PathNode *newNode = new PathNode(p, getCost(p), currNode, Move::WEST);
      visited.insert(newNode);
      discovered.insert(p);
      frontiers.push(newNode);
    }
    ++p.x;
    --p.y; // North
    if (inBounds(p) && isEmpty(p) && discovered.find(p) == discovered.end())
    {
      PathNode *newNode = new PathNode(p, getCost(p), currNode, Move::NORTH);
      visited.insert(newNode);
      discovered.insert(p);
      frontiers.push(newNode);
    }
  };

  PathNode *currNode = start;
  discover(currNode);
  currNode = frontiers.top();
  frontiers.pop();
  // std::cout << "(" << std::setfill('0') << std::setw(2) << currNode->point.x;
  // std::cout << "," << std::setfill('0') << std::setw(2) << currNode->point.y;
  // std::cout << "," << std::setfill('0') << std::setw(2) << currNode->point.z;
  // if (currNode->point == dst)
  //  std::cout << ")\nFound on turn " << i << "\npritority queue has " << frontiers.size();
  // unsigned short i = 1;

  while (!frontiers.empty())
  {
    discover(currNode);
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
    //++i;
  }
  // std::cout << "\n";

  // Free up Memory
  for (auto it = visited.begin(); it != visited.end(); ++it)
  {
    delete *it;
  }

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
