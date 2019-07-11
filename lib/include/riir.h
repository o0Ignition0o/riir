#ifndef RIIR
#define RIIR
#include <cstdint>

extern "C"
{
    void to_lower(char& str);
    void net_to_lower_case(char* str, uint32_t length);
}

#endif // RIIR
