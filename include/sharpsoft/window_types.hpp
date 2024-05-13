#pragma once

#include <inttypes.h>
#include <string>
#include "sharpsoft/basic_types.hpp"
#include "sharpsoft/enums.hpp"

namespace sharp
{
    class window_base
    {
    private:
        uint16_t posX, posY;
        uint16_t width, height;
        std::string title;
        window_flags flags;

    protected:
        window_base(const std::string& title, const int2& pos, const int2& size);

        virtual void paint() = 0;

    public:
        const int2 get_pos() const;
        const int2 get_size() const;
        const int_rect get_window_rect() const;
        const std::string get_title() const;
        const bool is_active() const;

        void set_pos(const int2& new_pos);
        void set_size(const int2& new_size);
        void set_window_rect(const int_rect& new_rect);
        void set_title(const std::string& new_title);

        void show();
        void hide();
    };
}
