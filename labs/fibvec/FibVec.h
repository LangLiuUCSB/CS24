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
  unsigned long capacity() const;
  unsigned long count() const;
  void insert(int value, unsigned long index);
  int lookup(unsigned long index) const;
  int pop();
  void push(int value);
  int remove(unsigned long index);
};

#endif
