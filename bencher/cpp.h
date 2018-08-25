#include <cstdint>
/**
* Checks whether the IPv4 address is valid according to RFC 3986 section 3.2.2.
*/
bool net_IsValidIPv4Addr(const char *addr, int32_t addrLen);