#include "VoxMap.h"
#include "Errors.h"

#define out std::cout

typedef unsigned short u2byte;

VoxMap::VoxMap(std::istream &stream)
{
  stream >> xLim >> yLim >> zLim;
  map_area = xLim * yLim;
  char schem[map_area]; // index = x + xLim * y
  std::memset(schem, 0b111, map_area);

  map_size = map_area * zLim;
  graph = new Node *[map_size]; // index = x + xLim * (y + yLim * z)

  std::string xLine;
  size_t baseIndex2D;
  size_t baseIndex3D = 0;
  size_t graphIndex;
  for (u2byte z = 0; z < zLim; z++)
  {
    out << "\nlvl " << z << " schem\n"; //! print scheme
    baseIndex2D = 0;
    for (u2byte y = 0; y < yLim; y++)
    {
      stream >> xLine;
      u2byte xQuad = 0;
      for (char ch : xLine)
      {
        char hex = hexToDec(ch);
        char bit_place = 0b1000;
        for (size_t i = baseIndex2D; i < baseIndex2D + 4; i++)
        {
          if ((hex & bit_place)) //? when curr is full
            schem[i] = 0b100;    //* track full in schem[]

          else if (schem[i] ^ 0b111) //? when curr is empty AND prev is non void
          {
            schem[i] >>= 1;    //* update non void in schem[]
            if (schem[i] >> 1) //? when prev is full (valid for new Node)
            {
              Node *newNode = new Node(xQuad + i - baseIndex2D, y, z); //* create new Node
              //! WEST
              if (xQuad + i - baseIndex2D && !(schem[i - 1] & 0b100)) //? when west exists and is Node
              {
                graphIndex = i - 1 + baseIndex3D;
                while (!graph[graphIndex])           //? while west is nullptr
                  graphIndex -= map_area;            //* fall
                newNode->west = graph[graphIndex];   //* new Node reaches west Node
                if (schem[i - 1])                    //? when west relation is symmetric
                  graph[graphIndex]->east = newNode; //* west Node reaches new Node
              }
              //! NORTH
              if (y && !(schem[i - xLim] & 0b100)) //? when north exists and is Node
              {
                graphIndex = i - xLim + baseIndex3D;
                while (!graph[graphIndex])            //? while north is nullptr
                  graphIndex -= map_area;             //* fall
                newNode->north = graph[graphIndex];   //* new Node reaches north Node
                if (schem[i - xLim])                  //? when north relation is symmetric
                  graph[graphIndex]->south = newNode; //* north Node reaches new Node
              }
              graph[i + baseIndex3D] = newNode; //* add newNode in graph[]
            }
            else if (schem[i]) //? when prev is new Node
            {
              //! WEST
              if (xQuad + i - baseIndex2D && !(schem[i - 1] ^ 0b10)) //? when west exists and is new Node
              {
                graph[i - map_area + baseIndex3D]->west = graph[i - 1 + baseIndex3D]; //* old Node reaches west Node
                graph[i - 1 + baseIndex3D]->east = graph[i - map_area + baseIndex3D]; //* west Node reaches old Node
              }
              //! NORTH
              if (y && !(schem[i - xLim] ^ 0b10)) //? when north exists and is new Node
              {
                graph[i - map_area + baseIndex3D]->north = graph[i - xLim + baseIndex3D]; //* old Node reaches north Node
                graph[i - xLim + baseIndex3D]->south = graph[i - map_area + baseIndex3D]; //* north Node reaches old Node
              }
            }
            else //? when prev is old Node
            {
              //! WEST
              if (xQuad + i - baseIndex2D && !(schem[i - 1] ^ 0b10)) //? when west exists and is new Node
              {
                graphIndex = i - map_area - map_area + baseIndex3D;
                while (!graph[graphIndex])                            //? while curr is nullptr
                  graphIndex -= map_area;                             //* fall
                graph[i - 1 + baseIndex3D]->east = graph[graphIndex]; //* west Node reaches old Node
              }
              //! NORTH
              if (y && !(schem[i - xLim] ^ 0b10)) //? when north exists and is new Node
              {
                graphIndex = i - map_area - map_area + baseIndex3D;
                while (!graph[graphIndex])                                //? while curr is nullptr
                  graphIndex -= map_area;                                 //* fall
                graph[i - xLim + baseIndex3D]->south = graph[graphIndex]; //* north Node reaches old Node
              }
            }
          }
          bit_place >>= 1;
        }
        xQuad += 4;
        baseIndex2D += 4;
      }
      //! print scheme
      for (size_t i = 0; i < 12; i++)
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
      out << "\n"; //! print scheme
    }
    baseIndex3D += map_area;
  }
  out << "\nNODES IN GRAPH\n"; //! print graph
  for (u2byte z = 4; z < 5; z++)
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
        // else
        //   out << "_";
      }
      out << "\n";
    }
    out << "\n";
  }
}

VoxMap::~VoxMap()
{
  for (size_t i = 0; i < map_size; i++)
    if (graph[i])
      delete graph[i];
  delete[] graph;
}

Route VoxMap::route(Point src, Point dst)
{
  throw NoRoute(src, dst);
}