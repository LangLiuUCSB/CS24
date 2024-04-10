#ifndef FIBVEC_H
#define FIBVEC_H

// This provides the size_t type:
#include <cstddef>

class FibVec
{
  // Member Variables
  int *vec;
  unsigned long vecSize;
  unsigned long vecCount;
  size_t nthFib;

  // Helper Functions
  unsigned long Fib(size_t n);

public:
  // Constructor and Destructor
  FibVec();
  ~FibVec();

  // Member Functions
  unsigned long capacity();
  unsigned long count();
  void insert(int value, unsigned long index);
  int lookup(unsigned long index);
  int pop();
  void push(int value);
  int remove(size_t index);
};

#endif
