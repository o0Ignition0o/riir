#include "cpp.h"
#include <cstdint>
#include "rangedPtr.h"

bool net_IsValidIPv4Addr(const char *addr, int32_t addrLen)
{
	RangedPtr<const char> p(addr, addrLen);

	int32_t octet = -1;   // means no digit yet
	int32_t dotCount = 0; // number of dots in the address

	for (; addrLen; ++p, --addrLen) {
		if (*p == '.') {
			dotCount++;
			if (octet == -1) {
				// invalid octet
				return false;
			}
			octet = -1;
		}
		else if (*p >= '0' && *p <= '9') {
			if (octet == 0) {
				// leading 0 is not allowed
				return false;
			}
			if (octet == -1) {
				octet = *p - '0';
			}
			else {
				octet *= 10;
				octet += *p - '0';
				if (octet > 255)
					return false;
			}
		}
		else {
			// invalid character
			return false;
		}
	}

	return (dotCount == 3 && octet != -1);
}
