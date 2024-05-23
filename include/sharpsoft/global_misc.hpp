#pragma once

#include "sharpsoft/basic_types.hpp"
#include "sharpsoft/window_types.hpp"

#define SHARPSOFT_INTERNAL
#include "internal.hpp"
#undef SHARPSOFT_INTERNAL

namespace sharp
{
    constexpr int screen_width = 480, screen_height = 240;

    struct global_properties
    {
        static const global_properties defaults;

        color background_color;
    };

    void initialize();
    void initialize(const global_properties& flags);
    void uninitialize();
    void re_initialize();
    void re_initialize(const global_properties& flags);
    bool is_initialized();

    template<typename T>
    void add_window(T window)
    {
        static_assert(std::is_base_of<window_base, T>::value);
        internal::add_window(&window, sizeof(T));
    }

    void start();
    void end();
    bool is_started();
}
