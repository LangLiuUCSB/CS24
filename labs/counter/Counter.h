#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>
#include <string>

#include "List.h"

// This is the Counter class you need to implement.
// It includes the Counter::Iterator as a nested class.

class Counter
{
public:
  class Iterator
  {
    // Member Variables
    List::Node *start;

  public:
    Iterator(List::Node *nodePtr) : start(nodePtr) {}
    const std::string &key() const;
    int value() const;

    void operator++();
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;
  };

private:
  struct Node
  {
    std::string key;
    int value;
    Node *next;
    List::Node *listNode;

    Node(const std::string &k, int v) : key(k), value(v), next(nullptr), listNode(nullptr) {}
  };
  // Member Variables
  Node **buckets;
  size_t numBuckets;
  size_t numKeys;
  List keysList;

private:
  // Helper Functions
  size_t hash(const std::string &key) const
  {
    size_t hash = 0;
    const char *data = reinterpret_cast<const char *>(&key);
    for (size_t i = 0; i < sizeof(std::string); ++i)
    {
      hash = hash * 31 + data[i];
    }
    return hash;
  }

  size_t getBucketIndex(const std::string &key) const
  {
    return hash(key) % numBuckets;
  }

public:
  Counter();
  ~Counter();

  size_t count() const;
  int total() const;

  void inc(const std::string &key, int by = 1);
  void dec(const std::string &key, int by = 1);
  void del(const std::string &key);
  int get(const std::string &key) const;
  void set(const std::string &key, int count);

  Iterator begin() const;
  Iterator end() const;
};

#endif