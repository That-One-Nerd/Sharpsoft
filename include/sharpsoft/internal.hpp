#pragma once

#ifdef SHARPSOFT_INTERNAL
#include "window_types.hpp"

namespace sharp
{
    namespace internal
    {
        void add_window(window_base* win_ptr, size_t size);
    }
}
#endif
