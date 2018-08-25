#ifndef RIIR
#define RIIR
#include <cstdint>

extern "C"
{
    bool rust_net_is_valid_ipv4_addr(const char *addr, int32_t addrLen);
    bool rust_net_is_valid_ipv4_addr_readable(const char *addr, int32_t addrLen);
}

#endif // RIIR
