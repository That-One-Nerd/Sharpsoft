#pragma once

#include "sharpsoft/basic_types.hpp"
#include "sharpsoft/window_types.hpp"

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

    void start();
    void end();
    bool is_started();
}
