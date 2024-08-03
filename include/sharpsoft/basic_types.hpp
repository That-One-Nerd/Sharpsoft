#pragma once

#include <cstdint>

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

        const int2 operator+(const int2& other) const;
        const int2 operator-(const int2& other) const;
        const int2 operator*(const int factor) const;
        const int2 operator/(const int factor) const;
    };
    struct float2
    {
        double x, y;

        float2();
        float2(double x, double y);

        double magnitude() const;

        operator int2() const;

        const float2 operator+(const float2& other) const;
        const float2 operator-(const float2& other) const;
        const float2 operator*(const double factor) const;
        const float2 operator/(const double factor) const;
    };

    struct int_rect
    {
        int left, top;
        int width, height;

        int_rect();
        int_rect(int left, int top, int width, int height);
        int_rect(const int2 pos, const int2 size);

        const int2 tl() const; // Top left
        const int2 tr() const; // Top right
        const int2 bl() const; // Bottom left
        const int2 br() const; // Bottom right

        bool contains(const int2& point) const;
        bool contains(const int_rect& rect) const; // Fully contains other rect.

        bool intersects(const int_rect& rect) const; // Partially contains other rect.
    };

    enum size
    {
        SMALL = -1,
        NORMAL = 0,
        LARGE = 1
    };
}
