#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
  FibVec fibvec;

  fibvec.push(747);

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  std::cout << "i = 0: " << fibvec.lookup(0) << "\n";

  int x = fibvec.remove(0);

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  std::cout << "removed: " << x << "\n";

  return 0;
}
