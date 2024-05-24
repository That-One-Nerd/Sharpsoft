#pragma once

#include <inttypes.h>

namespace sharp
{
    enum window_flags : uint32_t
    {
        CONTINUOUS_PAINT = 0x01,
        CONTINUOUS_TICK  = 0x02,
    };
}
