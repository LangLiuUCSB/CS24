#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
  FibVec fibvec;

  fibvec.insert(42, 0);

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  std::cout << fibvec.lookup(0) << "\n";

  fibvec.insert(69, 1);

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  std::cout << fibvec.lookup(1) << "\n";

  return 0;
}
