#pragma once

#include <inttypes.h>
#include "sharpsoft/basic_types.hpp"

namespace sharp
{
    class window_base
    {
    private:
        uint16_t posX, posY;
        uint16_t width, height;

    public:
        const int2 get_pos() const;
        const int2 get_size() const;
        const int_rect get_window_rect() const;

        void set_pos(const int2& new_pos);
        void set_size(const int2& new_size);
        void set_window_rect(const int_rect& new_rect);
    };
}
