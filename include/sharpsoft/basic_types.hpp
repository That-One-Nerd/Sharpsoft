#pragma once

#include <cstdint>
#include <numbers>

using std::numbers::pi;

namespace sharp
{
    enum angle_type
    {
        DEGREES  = 10,
        RADIANS  = 11,
        GRADIANS = 12,
        TURNS    = 13
    };
    struct angle
    {
    private:
        double value;

    public:
        angle();
        angle(const angle& copy);
        angle(double amount, angle_type unit);

        double get(angle_type unit) const;

        double degrees() const;
        double radians() const;
        double gradians() const;
        double turns() const;

        void set(double value, angle_type unit);

        void degrees(double deg);
        void radians(double rad);
        void gradians(double grad);
        void turns(double turns);

        const angle operator+(const angle& other) const;
        const angle operator-() const;
        const angle operator-(const angle& other) const;
        const angle operator*(double factor) const;
        const angle operator/(double factor) const;
    };
    const angle operator""_deg(long double val);
    const angle operator""_deg(unsigned long long val);
    const angle operator""_rad(long double val);
    const angle operator""_rad(unsigned long long val);
    const angle operator""_grad(long double val);
    const angle operator""_grad(unsigned long long val);
    const angle operator""_turns(long double val);
    const angle operator""_turns(unsigned long long val);

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

        static const int_rect from_corners(const int2& a, const int2& b);

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
