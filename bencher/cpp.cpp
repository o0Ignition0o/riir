#include "cpp.h"

void ToLower(char& c) {
  if ((unsigned)(c - 'A') <= (unsigned)('Z' - 'A')) c += 'a' - 'A';
}

int cpp_fibonacci(int n)
{
  if (n < 2) {
    return n;
  } else {
    return cpp_fibonacci(n - 1) + cpp_fibonacci(n - 2);
  }
}
