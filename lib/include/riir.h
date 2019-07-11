#ifndef RIIR
#define RIIR
#include <cstdint>

extern "C"
{
    int rust_fibonacci(int32_t n);
    void external_rust_to_lower(char& c);
}

#endif // RIIR
