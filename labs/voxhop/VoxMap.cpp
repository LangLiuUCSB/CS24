#include "VoxMap.h"
#include "Errors.h"

#include <cstdlib>
#include <algorithm>
#include <stdexcept>

VoxMap::VoxMap(std::istream &stream)
{
  stream >> xWidth >> yDepth >> zHeight;

  map = new std::bitset<4>[xWidth * yDepth * zHeight];

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
        size_t baseIndex = (z * yDepth + y) * xWidth + xQuad;

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
  if (!inBounds3D(src) || map[(src.z * yDepth + src.y) * xWidth + src.x] == 1 || map[((src.z - 1) * yDepth + src.y) * xWidth + src.x] != 1)
    throw InvalidPoint(src);
  if (!inBounds3D(dst) || map[(dst.z * yDepth + dst.y) * xWidth + dst.x] == 1 || map[((dst.z - 1) * yDepth + dst.y) * xWidth + dst.x] != 1)
    throw InvalidPoint(dst);

  Route path;

  auto getCost = [dst](Point p) -> unsigned short // Manhattan Distance from Destination
  { return abs(p.x - dst.x) + abs(p.y - dst.y) + abs(p.z - dst.z); };

  auto compare = [](const Point &a, const Point &b)
  { return a.cost > b.cost; };
  std::priority_queue<Point, std::vector<Point>, decltype(compare)> frontiers(compare);
  src.cost = getCost(src);
  frontiers.push(src);

  map[(src.z * yDepth + src.y) * xWidth + src.x] = 2;

  std::vector<std::vector<std::vector<Point>>> prevPoint(zHeight, std::vector<std::vector<Point>>(yDepth, std::vector<Point>(xWidth)));

  std::vector<std::vector<std::vector<Move>>> prevMove(zHeight, std::vector<std::vector<Move>>(yDepth, std::vector<Move>(xWidth)));

  Point currPoint;
  while (!frontiers.empty())
  {
    currPoint = frontiers.top();
    frontiers.pop();

    //! path found
    if (currPoint.cost == 0) // if Manhattan Distance from Destination is zero
    {
      while (currPoint != src)
      {
        path.push_back(prevMove[currPoint.z][currPoint.y][currPoint.x]);
        currPoint = prevPoint[currPoint.z][currPoint.y][currPoint.x];
      }
      std::reverse(path.begin(), path.end());
      for (size_t i = 0; i < xWidth * yDepth * zHeight; i++)
      {
        if (map[i] != 1)
          map[i] = 0;
      }
      return path;
    }

    //! scan adjacents and push frontiers
    Point newPoint;
    Point displacement[] = {Point(1, 0, 0), Point(0, 1, 0), Point(-1, 0, 0), Point(0, -1, 0)};
    for (Move direction : {Move::EAST, Move::SOUTH, Move::WEST, Move::NORTH})
    {
      newPoint = currPoint + displacement[direction];
      if (inBounds2D(newPoint)) // if newPoint in bounds
      {
        if (map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x] != 1) // if (newPoint) empty XXX0
        {
          //! newPoint fall
          --newPoint.z;          // fall down
          while (0 < newPoint.z) // while (newPoint) in z bound
          {
            if (map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x] == 1) // if (newPoint) full XXX1
              break;
            --newPoint.z; // fall down
          }
          ++newPoint.z; // fly up

          if (map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x] == 0 &&     // if (newPoint) unscanned XX0X
              map[((newPoint.z - 1) * yDepth + newPoint.y) * xWidth + newPoint.x] == 1) // if (newPoint below) full XXX1
          {
            map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x].set(1); // set (newPoint) scanned XX1X

            //! push frontier
            newPoint.cost = getCost(newPoint);
            frontiers.push(newPoint);

            //! track frontier prev
            prevPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;

            //! track move
            prevMove[newPoint.z][newPoint.y][newPoint.x] = direction;
            /*
            // set all above as visited
            ++newPoint.z;                // fly up
            while (newPoint.z < zHeight) // while (newPoint) in z bound
            {
              if (map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x] == 1) // if (newPoint) full XXX1
                break;
              map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x].set(1); // set scanned XX1X
              ++newPoint.z;                                                         // fly up
            }
            */
          }
        }
        else // if (newPoint) full XXX1
        {
          if (currPoint.z + 1 < zHeight &&                                                 // if (currPoint) in bounds
              map[((currPoint.z + 1) * yDepth + currPoint.y) * xWidth + currPoint.x] != 1) // if (newPoint above) empty XXX0
          {
            ++newPoint.z;                                                           // climb
            if (map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x] == 0) // if (newPoint) empty XXX0
            {
              map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x].set(1); // set (newPoint)scanned XX1X

              //! push frontier
              newPoint.cost = getCost(newPoint);
              frontiers.push(newPoint);

              //! track frontier prev
              prevPoint[newPoint.z][newPoint.y][newPoint.x] = currPoint;

              //! track move
              prevMove[newPoint.z][newPoint.y][newPoint.x] = direction;
              /*
              // set all above as visited
              ++newPoint.z;                // fly up
              while (newPoint.z < zHeight) // while (newPoint) in z bound
              {
                if (map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x] == 1) // if (newPoint) full XXX1
                  break;
                map[(newPoint.z * yDepth + newPoint.y) * xWidth + newPoint.x].set(1); // set scanned XX1X
                ++newPoint.z;                                                         // fly up
              }
              */
            }
          }
        }
      }
    }
  }
  for (size_t i = 0; i < xWidth * yDepth * zHeight; i++)
  {
    if (map[i] != 1)
      map[i] = 0;
  }
  throw NoRoute(src, dst);
}

void VoxMap::printMap(Point src, Point dst) const
{
  for (unsigned short z = 0; z < zHeight; z++)
  {
    std::cout << "Lvl: " << z << "\n";
    for (unsigned short y = 0; y < yDepth; y++)
    {
      for (unsigned short x = 0; x < xWidth; x++)
      {
        int index = (z * yDepth + y) * xWidth + x;
        if (index == (src.z * yDepth + src.y) * xWidth + src.x)
          std::cout << 's';
        else if (index == (dst.z * yDepth + dst.y) * xWidth + dst.x)
          std::cout << 'd';
        else
        {
          auto b = map[index];
          if (b == 0)
            std::cout << ' ';
          if (b == 1)
            std::cout << '#';
          if (b == 2)
            std::cout << '.';
        }
      }
      std::cout << "\n";
    }
  }
}
