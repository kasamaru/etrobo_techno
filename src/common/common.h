#include <cstdint>
#include <cstring>
using SBYTE = int8_t;
using BYTE = uint8_t;

using SWORD = int16_t;
using WORD = uint16_t;

using SDWORD = int32_t;
using DWORD = uint32_t;

#define MAX_SBYTE (127)
#define MIN_SBYTE (-128)
#define MAX_BYTE (255)
#define MIN_BYTE (0)
#define MAX_SWORD (32767)
#define MIN_SWORD (-32768)
#define MAX_WORD (65535)
#define MIN_WORD (0)
#define MAX_SDWORD (2147483647)
#define MIN_SDWORD (-2147483648)

#define MAX(src, dst) ((src > dst) ? src : dst)
#define MIN(src, dst) ((src < dst) ? src : dst)