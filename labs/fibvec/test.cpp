#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
  FibVec fibvec;

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";

  fibvec.push(42);

  std::cout << "count: " << fibvec.count() << "\n";
  std::cout << fibvec.lookup(0) << "\n";

  return 0;
}
