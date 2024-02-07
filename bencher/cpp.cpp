#include "cpp.h"
#include <cctype>
#include <algorithm>

void ToLower(char& c) {
  if ((unsigned)(c - 'A') <= (unsigned)('Z' - 'A')) c += 'a' - 'A';
}

void net_ToLowerCase(char* str, int length) {
  std::transform(str, str + length, str, 
    [](unsigned char c){ return std::tolower(c); }
  );
  // for (char* end = str + length; str < end; ++str) {
  //   *str = std::tolower(*str);
  // }
}
