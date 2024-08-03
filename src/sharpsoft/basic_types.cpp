#include "math.h"
#include "sharpsoft/basic_types.hpp"

using namespace sharp;

using std::max;
using std::min;

static constexpr double degrees_per_turn = 360;
static constexpr double radians_per_turn = 2 * pi;
static constexpr double gradians_per_turn = 400;

sharp::angle::angle()
{
    value = 0;
}
sharp::angle::angle(const angle& copy)
{
    value = copy.value;
}
sharp::angle::angle(double amount, angle_type unit)
{
    set(amount, unit);
}
double sharp::angle::get(angle_type unit) const
{
    switch (unit)
    {
        case DEGREES: return degrees();
        case RADIANS: return radians();
        case GRADIANS: return gradians();
        case TURNS: return turns();
        default: return 0.0;
    }
}
double sharp::angle::degrees() const
{
    return degrees_per_turn * value;
}
double sharp::angle::radians() const
{
    return radians_per_turn * value;
}
double sharp::angle::gradians() const
{
    return gradians_per_turn * value;
}
double sharp::angle::turns() const
{
    return value;
}
void sharp::angle::set(double value, angle_type unit)
{
    switch (unit)
    {
        case DEGREES: degrees(value);
        case RADIANS: radians(value);
        case GRADIANS: gradians(value);
        case TURNS: turns(value);
        default: return;
    }
}
void sharp::angle::degrees(double deg)
{
    value = deg / degrees_per_turn;
}
void sharp::angle::radians(double rad)
{
    value = rad / radians_per_turn;
}
void sharp::angle::gradians(double grad)
{
    value = grad / gradians_per_turn;
}
void sharp::angle::turns(double turns)
{
    value = turns;
}
// Doing this somewhat convoluted set system because I don't
// want to run unneccessary unit detection, I know I'm working
// with the raw turns.
const angle sharp::angle::operator+(const angle& other) const
{
    angle result = angle();
    result.value = value + other.value;
    return result;
}
const angle sharp::angle::operator-() const
{
    angle result = angle();
    result.value = -value;
    return result;
}
const angle sharp::angle::operator-(const angle& other) const
{
    angle result = angle();
    result.value = value - other.value;
    return result;
}
const angle sharp::angle::operator*(double factor) const
{
    angle result = angle();
    result.value = value * factor;
    return result;
}
const angle sharp::angle::operator/(double factor) const
{
    angle result = angle();
    result.value = value / factor;
    return result;
}
// These are shorthands.
const angle sharp::operator""_deg(long double val)
{
    return angle(val, DEGREES);
}
const angle sharp::operator""_deg(unsigned long long val)
{
    return angle(val, DEGREES);
}
const angle sharp::operator""_rad(long double val)
{
    return angle(val, RADIANS);
}
const angle sharp::operator""_rad(unsigned long long val)
{
    return angle(val, RADIANS);
}
const angle sharp::operator""_grad(long double val)
{
    return angle(val, GRADIANS);
}
const angle sharp::operator""_grad(unsigned long long val)
{
    return angle(val, GRADIANS);
}
const angle sharp::operator""_turns(long double val)
{
    return angle(val, TURNS);
}
const angle sharp::operator""_turns(unsigned long long val)
{
    return angle(val, TURNS);
}

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
const int_rect sharp::int_rect::from_corners(const int2& a, const int2& b)
{
    int2 tl = int2(min(a.x, b.x), min(a.y, b.y));
    int2 size = int2(max(a.x, b.x) - tl.x, max(a.y, b.y) - tl.y);
    return int_rect(tl, size);
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
