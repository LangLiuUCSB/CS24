#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
  FibVec fibvec;

  int removeH[] = {1, 2, 3, 6, 11, 23, 47, 106, 235, 551, 1301, 3159, 7741, 19320, 48629, 123867, 317955};
  for (int n : removeH)
  {
    fibvec.push(n);
  }

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  for (unsigned long i = 0; i < fibvec.count(); i++)
  {
    std::cout << " " << fibvec.lookup(i);
  }
  std::cout << "\n";

  std::cout << "removed: " << fibvec.remove(0) << "\n";

  std::cout << "capacity: " << fibvec.capacity() << "\n";
  std::cout << "count: " << fibvec.count() << "\n";
  for (unsigned long i = 0; i < fibvec.count(); i++)
  {
    std::cout << " " << fibvec.lookup(i);
  }
  std::cout << "\n";

  return 0;
}
