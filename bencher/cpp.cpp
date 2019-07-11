#include "cpp.h"

int cpp_fibonacci(int n)
{
  if (n < 2) {
    return n;
  } else {
    return cpp_fibonacci(n - 1) + cpp_fibonacci(n - 2);
  }
}
