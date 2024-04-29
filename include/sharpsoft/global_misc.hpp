#pragma once

#include "sharpsoft/basic_types.hpp"

namespace sharp
{
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
}
