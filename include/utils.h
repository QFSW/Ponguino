#pragma once

#include <inttypes.h>

namespace utils
{
    void divmod10(uint32_t in, uint32_t &div, uint8_t &mod) __attribute__((noinline));
}