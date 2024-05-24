#pragma once

#include <atomic>
#include <inttypes.h>
#include <string>
#include "sharpsoft/basic_types.hpp"

namespace sharp
{
    enum window_flags : uint32_t
    {
        CONTINUOUS_PAINT = 0x01,
        CONTINUOUS_TICK  = 0x02,
    };
    enum window_internal_flags : uint32_t
    {
        WINDOW_ACTIVE            = 0x01,
        WINDOW_VISIBLE           = 0x02,
        WINDOW_HEADER_VALIDATED  = 0x04,
        WINDOW_CONTENT_VALIDATED = 0x08
    };

    struct window_styles
    {
        static const window_styles defaults;

        color background_color;
        color outline_color;
    };

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
        window_internal_flags int_flags;
        window_styles styles;

        void paint_header() const;
        void paint_content_back() const;

#ifndef SHARPSOFT_INTERNAL
    protected:
#endif
        window_base(const std::string& title, const int2& pos, const int2& size);

        virtual void paint() = 0;
        virtual void tick() = 0;

    public:
        const window_styles& style() const;
        window_styles& style();

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
