#include "math.h"
#include "sharpsoft/basic_types.hpp"

using namespace sharp;


sharp::color::color()
{
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}
sharp::color::color(uint8_t r, uint8_t g, uint8_t b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    a = 0;
}
sharp::color::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
sharp::color::color(uint32_t rgb, uint8_t a)
{
    constexpr uint32_t bytemask = 0b11111111;
    this->a = a;
    r = (rgb >> 16) & bytemask;
    g = (rgb >>  8) & bytemask;
    b = (rgb      ) & bytemask;
}
sharp::color::color(uint32_t argb)
{
    constexpr uint32_t bytemask = 0b11111111;
    a = (argb >> 24); // bytemask not needed.
    r = (argb >> 16) & bytemask;
    g = (argb >>  8) & bytemask;
    b = (argb      ) & bytemask;
}

uint32_t sharp::color::get_value() const
{
    return (b      ) +
           (g <<  8) +
           (r << 16) +
           (a << 24);
}

sharp::int2::int2()
{
    x = 0;
    y = 0;
}
sharp::int2::int2(int x, int y)
{
    this->x = x;
    this->y = y;
}
double sharp::int2::magnitude() const
{
    return sqrt(x * x + y * y);
}
sharp::int2::operator float2() const
{
    return float2(x, y);
}

sharp::float2::float2()
{
    x = 0;
    y = 0;
}
sharp::float2::float2(double x, double y)
{
    this->x = x;
    this->y = y;
}
double sharp::float2::magnitude() const
{
    return sqrt(x * x + y * y);
}
sharp::float2::operator int2() const
{
    return int2(x, y);
};
