#pragma once

#include <inttypes.h>

#define CONCAT_(prefix, suffix) prefix##suffix
#define CONCAT(prefix, suffix) CONCAT_(prefix, suffix)
#define UNIQUE_VAR(prefix) CONCAT(prefix##_, __LINE__)

namespace utils
{
    void divmod10(uint32_t in, uint32_t &div, uint8_t &mod) __attribute__((noinline));
}