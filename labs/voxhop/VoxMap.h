#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <cstring>

#include "Point.h"
#include "Route.h"

struct Node
{
  short x, y, z;
  unsigned short cost;
  Node *next[4] = {nullptr, nullptr, nullptr, nullptr};
  Node *prev;
  Move move;
  unsigned char visit = 0;
  Node(short x, short y, short z) : x(x), y(y), z(z) {}
};

class Pairing_heap
{
  Node **heap;
  size_t count, parentIndex, smallest, left, right;

  void heapifyUp(size_t index)
  {
    while (index > 0)
    {
      parentIndex = (index - 1) / 2;
      if (heap[index]->cost >= heap[parentIndex]->cost)
        break;
      std::swap(heap[index], heap[parentIndex]);
      index = parentIndex;
    }
  }
  void heapifyDown(size_t index)
  {
    smallest = index;
    left = 2 * index + 1;
    right = left + 1;
    if (left < count && heap[left]->cost < heap[smallest]->cost)
      smallest = left;
    if (right < count && heap[right]->cost < heap[smallest]->cost)
      smallest = right;
    if (smallest != index)
    {
      std::swap(heap[index], heap[smallest]);
      heapifyDown(smallest);
    }
  }

public:
  Pairing_heap(size_t maxSize) : heap(new Node *[maxSize]), count(0) {}
  ~Pairing_heap() { delete[] heap; }

  inline void push(Node *node)
  {
    heap[count] = node;
    heapifyUp(count);
    count++;
  }
  inline Node *pop()
  {
    Node *popped_node = heap[0];
    heap[0] = heap[count - 1];
    count--;
    heapifyDown(0);
    return popped_node;
  }
  inline bool empty() const { return count == 0; }
  inline void clear() { count = 0; }
};

class VoxMap
{
  // Member Variables
  unsigned short xLim, yLim, zLim;
  size_t map_area, map_volume;
  Node **graph;
  Pairing_heap *frontiers;

  Node *srcNode, *dstNode, *currNode, *adjNode;
  static constexpr Move cardinal_directions[4] = {Move::EAST, Move::SOUTH, Move::WEST, Move::NORTH};
  unsigned char currVisit = 1;

  // Helper Functions
  inline char hexToDec(char hex) const { return (hex <= '9') ? hex - '0' : hex - 'W'; }
  Node *getNode(short x, short y, short z) const { return graph[x + xLim * (y + yLim * z)]; };
  inline bool inBounds(short x, short y, short z) { return x < xLim && y < yLim && z < zLim; }

public:
  VoxMap(std::istream &stream);
  ~VoxMap();

  Route route(Point src, Point dst);

  void printMap(Point src, Point dst) const;
};

#endif
