#include "VoxMap.h"
#include "Errors.h"

#define out std::cout

typedef unsigned short u2byte;

VoxMap::VoxMap(std::istream &stream)
{
  stream >> xLim >> yLim >> zLim;
  map_area = xLim * yLim;
  char schem[map_area]; // index = x + xLim * y

  map_volume = map_area * zLim;
  graph = new Node *[map_volume]; // index = x + xLim * (y + yLim * z)
  std::memset(graph, 0, map_volume * sizeof(Node *));

  std::string xLine;
  unsigned short x_quad;
  size_t area_north = 0;
  //! z=0 parse
  for (unsigned short y = 0; y < yLim; y++)
  {
    stream >> xLine;
    x_quad = 0;
    for (char ch : xLine)
    {
      char hex = hexToDec(ch);
      char bit_place = 0b1000;
      for (size_t i = area_north; i < area_north + 4; i++)
      {
        if ((hex & bit_place)) //? when curr is full
          schem[i] = 0b100;    //* track full in schem[]
        else                   //? when curr is non void
          schem[i] = 0b111;
        bit_place >>= 1;
      }
      x_quad += 4;
      area_north += 4;
    }
  }
  //! default parse
  size_t graphIndex;
  size_t volume_below = map_area;
  for (unsigned short z = 1; z < zLim; z++)
  {
    area_north = 0;
    for (unsigned short y = 0; y < yLim; y++)
    {
      stream >> xLine;
      x_quad = 0;
      for (char ch : xLine)
      {
        char hex = hexToDec(ch);
        char bit_place = 0b1000;
        for (size_t i = area_north; i < area_north + 4; i++)
        {
          if ((hex & bit_place))     //? when curr is full
            schem[i] = 0b100;        //* track full in schem[]
          else if (schem[i] ^ 0b111) //? when curr is empty AND prev is non void
          {
            schem[i] >>= 1;    //* update non void in schem[]
            if (schem[i] >> 1) //? when prev is full (valid for new Node)
            {
              Node *newNode = new Node(x_quad + i - area_north, y, z); //* create new Node
              //! WEST
              if (x_quad + i - area_north && !(schem[i - 1] & 0b100)) //? when west exists and is Node
              {
                graphIndex = i - 1 + volume_below;
                while (!graph[graphIndex])           //? while west is nullptr
                  graphIndex -= map_area;            //* fall
                newNode->west = graph[graphIndex];   //* new Node reaches west Node
                if (schem[i - 1])                    //? when west relation is symmetric
                  graph[graphIndex]->east = newNode; //* west Node reaches new Node
              }
              //! NORTH
              if (y && !(schem[i - xLim] & 0b100)) //? when north exists and is Node
              {
                graphIndex = i - xLim + volume_below;
                while (!graph[graphIndex])            //? while north is nullptr
                  graphIndex -= map_area;             //* fall
                newNode->north = graph[graphIndex];   //* new Node reaches north Node
                if (schem[i - xLim])                  //? when north relation is symmetric
                  graph[graphIndex]->south = newNode; //* north Node reaches new Node
              }
              graph[i + volume_below] = newNode; //* add newNode in graph[]
            }
            else if (schem[i]) //? when prev is new Node
            {
              //! WEST
              if (x_quad + i - area_north && !(schem[i - 1] ^ 0b10)) //? when west exists and is new Node
              {
                graph[i - map_area + volume_below]->west = graph[i - 1 + volume_below]; //* old Node reaches west Node
                graph[i - 1 + volume_below]->east = graph[i - map_area + volume_below]; //* west Node reaches old Node
              }
              //! NORTH
              if (y && !(schem[i - xLim] ^ 0b10)) //? when north exists and is new Node
              {
                graph[i - map_area + volume_below]->north = graph[i - xLim + volume_below]; //* old Node reaches north Node
                graph[i - xLim + volume_below]->south = graph[i - map_area + volume_below]; //* north Node reaches old Node
              }
            }
            else //? when prev is old Node
            {
              //! WEST
              if (x_quad + i - area_north && !(schem[i - 1] ^ 0b10)) //? when west exists and is new Node
              {
                graphIndex = i - map_area - map_area + volume_below;
                while (!graph[graphIndex])                             //? while curr is nullptr
                  graphIndex -= map_area;                              //* fall
                graph[i - 1 + volume_below]->east = graph[graphIndex]; //* west Node reaches old Node
              }
              //! NORTH
              if (y && !(schem[i - xLim] ^ 0b10)) //? when north exists and is new Node
              {
                graphIndex = i - 2 * map_area + volume_below;
                while (!graph[graphIndex])                                 //? while curr is nullptr
                  graphIndex -= map_area;                                  //* fall
                graph[i - xLim + volume_below]->south = graph[graphIndex]; //* north Node reaches old Node
              }
            }
          }
          bit_place >>= 1;
        }
        x_quad += 4;
        area_north += 4;
      }
    }
    volume_below += map_area;
  }
}

VoxMap::~VoxMap()
{
  for (size_t i = 0; i < map_volume; i++)
    if (graph[i])
      delete graph[i];
  delete[] graph;
}

Route VoxMap::route(Point src, Point dst)
{
  const short xs = src.x;
  const short ys = src.y;
  const short zs = src.z;
  const short xd = dst.x;
  const short yd = dst.y;
  const short zd = dst.z;

  if (!inBounds3D(xs, ys, zs) || !getNode(xs, ys, zs))
    throw InvalidPoint(src);
  if (!inBounds3D(xd, yd, zd) || !getNode(xd, yd, zd))
    throw InvalidPoint(dst);

  Route path;

  auto setCost = [xd, yd, zd](Node *n)
  { n->cost = abs(xd - n->x) + abs(yd - n->y) + abs(zd - n->z); }; // Manhattan Distance from Destination

  auto compare = [](Node *const &n1, Node *const &n2)
  { return n1->cost > n2->cost; };
  std::priority_queue<Node *, std::vector<Node *>, decltype(compare)> frontiers(compare);

  std::unordered_set<Node *> visited;
  std::unordered_map<Node *, Node *> came_from;
  std::unordered_map<Node *, Move> move;

  Node *srcNode = getNode(xs, ys, zs);
  setCost(srcNode);
  frontiers.push(srcNode);

  Node *dstNode = getNode(xd, yd, zd);

  Node *currNode;
  while (!frontiers.empty())
  {
    currNode = frontiers.top();
    frontiers.pop();

    if (currNode == dstNode)
    {
      while (currNode != srcNode)
      {
        currNode = came_from[currNode];
        path.push_back(move[currNode]);
      }
      std::reverse(path.begin(), path.end());
      return path;
    }

    visited.insert(currNode);

    Node *neighbor = currNode->east;
    if (neighbor && visited.find(neighbor) == visited.end())
    {
      setCost(neighbor);
      frontiers.push(neighbor);
      came_from[neighbor] = currNode;
      move[neighbor] = Move::EAST;
    }
    neighbor = currNode->south;
    if (neighbor && visited.find(neighbor) == visited.end())
    {
      setCost(neighbor);
      frontiers.push(neighbor);
      came_from[neighbor] = currNode;
      move[neighbor] = Move::SOUTH;
    }
    neighbor = currNode->west;
    if (neighbor && visited.find(neighbor) == visited.end())
    {
      setCost(neighbor);
      frontiers.push(neighbor);
      came_from[neighbor] = currNode;
      move[neighbor] = Move::WEST;
    }
    neighbor = currNode->north;
    if (neighbor && visited.find(neighbor) == visited.end())
    {
      setCost(neighbor);
      frontiers.push(neighbor);
      came_from[neighbor] = currNode;
      move[neighbor] = Move::NORTH;
    }
  }

  throw NoRoute(src, dst);
}

/*

      // TODO print scheme
      for (size_t i = 0; i < 0; i++)
      {
        switch (schem[i + xLim * y])
        {
        case 0b000:
          out << ".";
          break;
        case 0b001:
          out << ":";
          break;
        case 0b010:
          out << "+";
          break;
        case 0b100:
          out << "#";
          break;
        default:
          out << "_";
        }
      }
      // out << "\n"; // TODO print scheme
*/

/*

  // out << "\nNODES IN GRAPH\n"; // TODO print graph
  for (u2byte z = 0; z < 0; z++)
  {
    for (u2byte y = 0; y < yLim; y++)
    {
      for (u2byte x = 0; x < yLim; x++)
      {
        if (graph[x + xLim * (y + yLim * z)])
        {
          // out << "O";
          if (graph[x + xLim * (y + yLim * z)]->east)
          {
            out << "east(";
            out << graph[x + xLim * (y + yLim * z)]->east->x << ",";
            out << graph[x + xLim * (y + yLim * z)]->east->y << ",";
            out << graph[x + xLim * (y + yLim * z)]->east->z << ") ";
          }
          if (graph[x + xLim * (y + yLim * z)]->south)
          {
            out << "south(";
            out << graph[x + xLim * (y + yLim * z)]->south->x << ",";
            out << graph[x + xLim * (y + yLim * z)]->south->y << ",";
            out << graph[x + xLim * (y + yLim * z)]->south->z << ") ";
          }
          if (graph[x + xLim * (y + yLim * z)]->west)
          {
            out << "west(";
            out << graph[x + xLim * (y + yLim * z)]->west->x << ",";
            out << graph[x + xLim * (y + yLim * z)]->west->y << ",";
            out << graph[x + xLim * (y + yLim * z)]->west->z << ") ";
          }
          if (graph[x + xLim * (y + yLim * z)]->north)
          {
            out << "north(";
            out << graph[x + xLim * (y + yLim * z)]->north->x << ",";
            out << graph[x + xLim * (y + yLim * z)]->north->y << ",";
            out << graph[x + xLim * (y + yLim * z)]->north->z << ") ";
          }
          out << "\n";
        }
        // else // TODO print graph
        //   out << "_";
      }
      out << "\n";
    }
    out << "\n";
  }
*/
