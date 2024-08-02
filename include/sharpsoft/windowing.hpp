#pragma once

#include <string>
#include "sharpsoft/basic_types.hpp"

namespace sharp
{
    enum window_internal_flags : uint32_t
    {
        WINDOW_ACTIVE            = 0x01,
        WINDOW_VISIBLE           = 0x02,
        WINDOW_HEADER_VALIDATED  = 0x04,
        WINDOW_CONTENT_VALIDATED = 0x08
    };

    struct window_features
    {
        static const window_features defaults;

        bool continuous_paint; // Re-validate the content every frame. Otherwise, only when content is invalidated.
        bool continuous_tick;  // Call tick every frame. Otherwise, never called.
        bool update_header;    // If set, update header along with content. Otherwise, only when header is invalidated.

        bool show_header;      // If not set, the header will not be rendered. The outline still will.
    };
    struct window_styles
    {
        static const window_styles defaults;

        color background_color;
        color outline_color;
        color header_color;

        size header_size;
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
        window_internal_flags int_flags;

        window_features win_features;
        window_styles styles;

        void paint_header() const;
        void paint_content_back() const;

#ifndef SHARPSOFT_INTERNAL
    protected:
#endif
        window_base(const std::string& title, const int2& pos, const int2& size);
        virtual ~window_base();

        virtual void paint() = 0;
        virtual void tick() = 0;

    public:
        const window_styles& style() const;
        window_styles& style();

        const window_features& features() const;
        window_features& features();

        const int2 get_pos() const;
        const int2 get_size() const;
        const int_rect get_content_rect() const;
        const int_rect get_header_rect() const;
        int get_header_height() const;
        const int_rect get_window_rect() const;
        const std::string get_title() const;
        bool is_active() const;
        bool is_visible() const;

        void set_pos(const int2& new_pos);
        void set_size(const int2& new_size);
        void set_window_rect(const int_rect& new_rect);
        void set_title(const std::string& new_title);

        void invalidate();

        void show();
        void hide();
    };

    int get_header_height(size size);
}
