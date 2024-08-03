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
const int2 sharp::int2::operator+(const int2& other) const
{
    return int2(x + other.x, y + other.y);
}
const int2 sharp::int2::operator-(const int2& other) const
{
    return int2(x - other.x, y - other.y);
}
const int2 sharp::int2::operator*(const int factor) const
{
    return int2(x * factor, y * factor);
}
const int2 sharp::int2::operator/(const int factor) const
{
    return int2(x / factor, y / factor);
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
const float2 sharp::float2::operator+(const float2& other) const
{
    return float2(x + other.x, y + other.y);
}
const float2 sharp::float2::operator-(const float2& other) const
{
    return float2(x - other.x, y - other.y);
}
const float2 sharp::float2::operator*(const double factor) const
{
    return float2(x * factor, y * factor);
}
const float2 sharp::float2::operator/(const double factor) const
{
    return float2(x / factor, y / factor);
}

sharp::int_rect::int_rect()
{
    left = 0;
    top = 0;
    width = 0;
    height = 0;
}
sharp::int_rect::int_rect(int left, int top, int width, int height)
{
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
}
sharp::int_rect::int_rect(const int2 pos, const int2 size)
{
    left = pos.x;
    top = pos.y;
    width = size.x;
    height = size.y;
}

const int2 sharp::int_rect::tl() const
{
    return int2(top, left);
}
const int2 sharp::int_rect::tr() const
{
    return int2(top, left + width);
}
const int2 sharp::int_rect::bl() const
{
    return int2(top + height, left);
}
const int2 sharp::int_rect::br() const
{
    return int2(top + height, left + width);
}

bool sharp::int_rect::contains(const int2& point) const
{
    return point.x >= left && point.x <= left + width &&
           point.y >= top  && point.y <= top + height;
}
bool sharp::int_rect::contains(const int_rect& rect) const
{
    return contains(rect.tl()) && contains(rect.tr());
}

bool sharp::int_rect::intersects(const int_rect& rect) const
{
    // Top row is if this rect contains point of other rect.
    // Bottom row is if other rect contains point of this rect.
    return contains(rect.tl()) || contains(rect.tr()) || contains(rect.bl()) || contains(rect.br()) ||
           rect.contains(tl()) || rect.contains(tr()) || rect.contains(bl()) || rect.contains(br());
}
