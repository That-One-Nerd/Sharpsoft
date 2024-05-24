#define SHARPSOFT_INTERNAL

#include "sharpsoft/internal.hpp"
#include "sharpsoft/macros.hpp"
#include "sharpsoft/windowing.hpp"

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

void window_base::paint_header() const
{
    // Draw outline.
    internal::draw_global_rectangle(styles.outline_color, int_rect(posX - 1, posY - 1, width + 2, height + 2));
}
void window_base::paint_content_back() const
{
    // Draw background.
    internal::fill_global_rectangle(styles.background_color, int_rect(posX, posY, width, height));
}
