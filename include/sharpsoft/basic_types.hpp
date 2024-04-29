#pragma once

#include <inttypes.h>

namespace sharp
{
    struct color
    {
        uint8_t r, g, b, a;

        color();
        color(uint8_t r, uint8_t g, uint8_t b);
        color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        color(uint32_t rgb, uint8_t a);
        color(uint32_t argb);

        uint32_t get_value() const;
    };

    struct float2;

    struct int2
    {
        int x, y;

        int2();
        int2(int x, int y);

        double magnitude() const;
        
        operator float2() const;
    };
    struct float2
    {
        double x, y;

        float2();
        float2(double x, double y);

        double magnitude() const;

        operator int2() const;
    };
}
