#include "cpp.h"

void ToLower(char& c) {
  if ((unsigned)(c - 'A') <= (unsigned)('Z' - 'A')) c += 'a' - 'A';
}

void net_ToLowerCase(char* str, int length) {
  for (char* end = str + length; str < end; ++str) ToLower(*str);
}
