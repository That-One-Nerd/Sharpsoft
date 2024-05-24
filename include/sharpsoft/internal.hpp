#pragma once

#ifdef SHARPSOFT_INTERNAL
#include "basic_types.hpp"
#include "windowing.hpp"

#define HAS_WINDOW_FLAG(pwin, flag) ((pwin->flags & flag) > 0)
#define HAS_INTERNAL_FLAG(pwin, flag) ((pwin->int_flags & flag) > 0)
#define ON_INTERNAL_FLAG(pwin, flag) pwin->int_flags = (window_internal_flags)(pwin->int_flags | flag)
#define OFF_INTERNAL_FLAG(pwin, flag) pwin->int_flags = (window_internal_flags)(pwin->int_flags & ~flag)

namespace sharp
{
    namespace internal
    {
        void add_window(window_base* win_ptr, size_t size);
        
        void render_iter();
        void render_loop();

        void draw_global_rectangle(const color& color, const int_rect& rect);
        void fill_global_rectangle(const color& color, const int_rect& rect);
    }
}
#endif
