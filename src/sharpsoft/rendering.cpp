#define SHARPSOFT_INTERNAL

#include "sharpsoft/internal.hpp"
#include "sharpsoft/macros.hpp"
#include "sharpsoft/window_types.hpp"

#ifdef SH_PROS_ACTIVE
#include "pros/screen.hpp"
#endif

using namespace sharp;

#ifdef SH_PROS_ACTIVE
void internal::draw_global_rectangle(const color& color, const int_rect& rect)
{
    pros::screen::set_pen(color.get_value());
    pros::screen::draw_rect(rect.left, rect.top, rect.left + rect.width - 1, rect.top + rect.height - 1);
}
void internal::fill_global_rectangle(const color& color, const int_rect& rect)
{
    pros::screen::set_pen(color.get_value());
    pros::screen::fill_rect(rect.left, rect.top, rect.left + rect.width - 1, rect.top + rect.height - 1);
}
#endif

void window_base::paint_header()
{
    // Draw outline.
    const color outline_color = color(255, 255, 255);
    internal::draw_global_rectangle(outline_color, int_rect(posX - 1, posY - 1, width + 1, height + 1));
}
