#define SHARPSOFT_INTERNAL

#include "sharpsoft/internal.hpp"
#include "sharpsoft/macros.hpp"
#include "sharpsoft/windowing.hpp"

#ifdef SH_PROS_ACTIVE
#include "pros/screen.hpp"
#endif

using namespace sharp;

#ifdef SH_PROS_ACTIVE
void internal::draw_global_pixel(const color& color, const int2& pos)
{
    pros::screen::set_pen(color.get_value());
    pros::screen::draw_pixel(pos.x, pos.y);
}
void internal::draw_global_line(const color& color, const int2& start, const int2& end)
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

void window_base::draw_pixel(const color& color, const int2& win_pos)
{
    if (win_pos.x < 0 || win_pos.x >= width ||
        win_pos.y < 0 || win_pos.y >= height) return; // Out of window bounds.

    const int2 true_pos = to_screen(win_pos);
    internal::draw_global_pixel(color, true_pos);
}
void window_base::draw_line(const color& color, const int2& pos_a, const int2& pos_b)
{
    // FIXME: This causes artifacts occasionally along the top and bottom of the window.
    //        Why?

    double slope = (double)(pos_b.y - pos_a.y) / (pos_b.x - pos_a.x),
           inv_slope = (double)(pos_b.x - pos_a.x) / (pos_b.y - pos_a.y); // Prevent divide by zero errors.

    int2 a = pos_a, b = pos_b;
    if (a.x < 0) a = int2(0, -a.x * slope + a.y); // Left wall truncate for A.
    else if (a.x >= width) a = int2(width - 1, ((width - 1) - a.x) * slope + a.y); // Right wall truncate for A.
    if (a.y < 0) a = int2(-a.y * inv_slope + a.x, 0); // Bottom wall truncate for A.
    else if (a.y >= height) a = int2(((height - 1) - a.y) * inv_slope + a.x, height - 1); // Top wall truncate for A.

    if (b.x < 0) b = int2(0, -a.x * slope + a.y); // Left wall truncate for B.
    else if (b.x >= width) b = int2(width - 1, ((width - 1) - a.x) * slope + a.y); // Right wall truncate for B.
    if (b.y < 0) b = int2(-a.y * inv_slope + a.x, 0); // Bottom wall truncate for B.
    else if (b.y >= height) b = int2(((height - 1) - a.y) * inv_slope + a.x, height - 1); // Top wall truncate for B.

    const int2 true_pos_a = to_screen(a),
               true_pos_b = to_screen(b);
    internal::draw_global_line(color, true_pos_a, true_pos_b);
}
