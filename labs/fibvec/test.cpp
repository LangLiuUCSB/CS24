#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
  FibVec fibvec;

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";

  // fibvec.push(42);
  fibvec.insert(42, 0);

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  std::cout << "i = 0: " << fibvec.lookup(0) << "\n";

  // fibvec.push(69);
  fibvec.insert(69, 0);

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  std::cout << "i = 0: " << fibvec.lookup(0) << "\n";
  std::cout << "i = 1: " << fibvec.lookup(1) << "\n";

  return 0;
}
