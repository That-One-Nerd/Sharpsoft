#define SHARPSOFT_INTERNAL

#include "sharpsoft/internal.hpp"
#include "sharpsoft/macros.hpp"
#include "sharpsoft/windowing.hpp"

#ifdef SH_PROS_ACTIVE
#include "pros/screen.hpp"
#endif

using namespace sharp;

#ifdef SH_PROS_ACTIVE
void internal::draw_global_line(const color &color, const int2 &start, const int2 &end)
{
    pros::screen::set_pen(color.get_value());
    pros::screen::draw_line(start.x, start.y, end.x, end.y);
}
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
    internal::draw_global_rectangle(styles.outline_color, get_window_rect());

    int header_height = get_header_height();
    if (header_height > 0)
    {
        // Draw line between header and content.
        internal::draw_global_line(
            styles.outline_color,
            int2(
                posX,
                posY + header_height
            ),
            int2(
                posX + width,
                posY + header_height
            )
        );

        // Draw header.
        internal::fill_global_rectangle(styles.header_color, get_header_rect());
    }
}
void window_base::paint_content_back() const
{
    internal::fill_global_rectangle(styles.background_color, get_content_rect());
}
