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

bool net_IsValidIPv6Addr(const char *addr, int32_t addrLen) {
  RangedPtr<const char> p(addr, addrLen);

  int32_t digits = 0;      // number of digits in current block
  int32_t colons = 0;      // number of colons in a row during parsing
  int32_t blocks = 0;      // number of hexadecimal blocks
  bool haveZeros = false;  // true if double colon is present in the address

  for (; addrLen; ++p, --addrLen) {
    if (*p == ':') {
      if (colons == 0) {
        if (digits != 0) {
          digits = 0;
          blocks++;
        }
      } else if (colons == 1) {
        if (haveZeros) return false;  // only one occurrence is allowed
        haveZeros = true;
      } else {
        // too many colons in a row
        return false;
      }
      colons++;
    } else if ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') ||
               (*p >= 'A' && *p <= 'F')) {
      if (colons == 1 && blocks == 0)  // starts with a single colon
        return false;
      if (digits == 4)  // too many digits
        return false;
      colons = 0;
      digits++;
    } else if (*p == '.') {
      // check valid IPv4 from the beginning of the last block
      if (!net_IsValidIPv4Addr(p.get() - digits, addrLen)) {
        return false;
      }
      return (haveZeros && blocks < 6) || (!haveZeros && blocks == 6);
    } else {
      // invalid character
      return false;
    }
  }

  if (colons == 1)  // ends with a single colon
    return false;

  if (digits)  // there is a block at the end
    blocks++;

  return (haveZeros && blocks < 8) || (!haveZeros && blocks == 8);
}
