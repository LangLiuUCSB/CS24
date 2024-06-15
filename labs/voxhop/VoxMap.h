#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <cstring>
#include <algorithm>

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

struct CompareNode
{
  bool operator()(const Node &n1, const Node &n2) { return n1.cost > n2.cost; }
};

struct PairingHeapNode
{
  Node *data;
  PairingHeapNode *child;
  PairingHeapNode *sibling;
  PairingHeapNode *prev;

  PairingHeapNode(Node *node) : data(node), child(nullptr), sibling(nullptr), prev(nullptr) {}
};

class PairingHeap
{
private:
  PairingHeapNode *root;

  PairingHeapNode *merge(PairingHeapNode *node1, PairingHeapNode *node2)
  {
    if (!node1)
      return node2;
    if (!node2)
      return node1;

    if (node1->data->cost < node2->data->cost)
    {
      node2->prev = node1;
      node2->sibling = node1->child;
      if (node2->sibling)
        node2->sibling->prev = node2;
      node1->child = node2;
      return node1;
    }
    else
    {
      node1->prev = node2;
      node1->sibling = node2->child;
      if (node1->sibling)
        node1->sibling->prev = node1;
      node2->child = node1;
      return node2;
    }
  }

  PairingHeapNode *mergePairs(PairingHeapNode *node)
  {
    if (!node || !node->sibling)
      return node;

    PairingHeapNode *next = node->sibling->sibling;
    PairingHeapNode *merged = merge(node, node->sibling);

    return merge(merged, mergePairs(next));
  }

public:
  PairingHeap() : root(nullptr) {}

  void push(Node *node)
  {
    PairingHeapNode *newNode = new PairingHeapNode(node);
    root = merge(root, newNode);
  }

  Node *pop()
  {
    if (!root)
      return nullptr;
    Node *minNode = root->data;
    PairingHeapNode *oldRoot = root;
    root = mergePairs(root->child);
    if (root)
      root->prev = nullptr;
    delete oldRoot;
    return minNode;
  }

  bool empty() const
  {
    return root == nullptr;
  }

  void clear()
  {
    while (!empty())
    {
      pop();
    }
  }
};

class VoxMap
{
  // Member Variables
  unsigned short xLim, yLim, zLim;
  size_t map_area, map_volume;
  Node **graph;
  PairingHeap *frontiers;
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
