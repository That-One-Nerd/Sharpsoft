#pragma once

#include <atomic>
#include <inttypes.h>
#include <string>
#include "sharpsoft/basic_types.hpp"
#include "sharpsoft/enums.hpp"

namespace sharp
{
    class window_base
    {
#ifdef SHARPSOFT_INTERNAL
    public:
#else
    private:
#endif
        uint16_t posX, posY;
        uint16_t width, height;
        std::string title;
        window_flags flags;
        bool active, visible;

        bool header_validated;
        bool content_validated;

        void paint_header();

#ifndef SHARPSOFT_INTERNAL
    protected:
#endif
        window_base(const std::string& title, const int2& pos, const int2& size);

        virtual void paint() = 0;
        virtual void tick() = 0;

    public:
        bool get_flag(window_flags flag) const;
        const int2 get_pos() const;
        const int2 get_size() const;
        const int_rect get_window_rect() const;
        const std::string get_title() const;
        bool is_active() const;
        bool is_visible() const;

        void set_flag(window_flags flag, bool value);
        void set_pos(const int2& new_pos);
        void set_size(const int2& new_size);
        void set_window_rect(const int_rect& new_rect);
        void set_title(const std::string& new_title);

        void invalidate();

        void show();
        void hide();
    };
}
