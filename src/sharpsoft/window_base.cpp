#define SHARPSOFT_INTERNAL

#include "sharpsoft/internal.hpp"
#include "sharpsoft/windowing.hpp"

using std::string;
using namespace sharp;

sharp::window_base::window_base(const string& title, const int2& pos, const int2& size)
{
    this->title = title;
    posX = pos.x;
    posY = pos.y;
    width = size.x;
    height = size.y;
    int_flags = (window_internal_flags)WINDOW_VISIBLE;

    win_features = window_features::defaults;
    styles = window_styles::defaults;

    elapsed_time = 0;
}
sharp::window_base::~window_base()
{
    // Dispose of window.
    title.~basic_string();
}

const window_styles& sharp::window_base::style() const
{
    return styles;
}
window_styles& sharp::window_base::style()
{
    return styles;
}
const window_features& sharp::window_base::features() const
{
    return win_features;
}
window_features& sharp::window_base::features()
{
    return win_features;
}
double sharp::window_base::get_elapsed_time() const
{
    return elapsed_time;
}
const int2 sharp::window_base::get_pos() const
{
    return int2(posX, posY);
}
const int2 sharp::window_base::get_size() const
{
    return int2(width, height);
}
const int_rect sharp::window_base::get_content_rect() const
{
    int header_height = get_header_height();
    if (header_height > 0) return int_rect(posX, posY + header_height + 1, width, height);
    else return int_rect(posX, posY, width, height);
}
const int_rect sharp::window_base::get_header_rect() const
{
    return int_rect(posX, posY, width, get_header_height());
}
int sharp::window_base::get_header_height() const
{
    if (win_features.show_header) return sharp::get_header_height(styles.header_size);
    else return 0;
}
const int_rect sharp::window_base::get_window_rect() const
{
    int header_height = get_header_height();
    if (header_height > 0) return int_rect(posX - 1, posY - 1, width + 2, height + header_height + 3);
    else return int_rect(posX - 1, posY - 1, width + 2, height + 2);
}
const string sharp::window_base::get_title() const
{
    return title;
}
bool sharp::window_base::is_active() const
{
    return HAS_INTERNAL_FLAG(this, WINDOW_ACTIVE);
}
bool sharp::window_base::is_visible() const
{
    return HAS_INTERNAL_FLAG(this, WINDOW_VISIBLE);
}

void sharp::window_base::set_pos(const int2& new_pos)
{
    // TODO: This will affect windows below it.

    posX = new_pos.x;
    posY = new_pos.y;    
    OFF_INTERNAL_FLAG(this, WINDOW_HEADER_VALIDATED);
    OFF_INTERNAL_FLAG(this, WINDOW_CONTENT_VALIDATED);
}
void sharp::window_base::set_size(const int2& new_pos)
{
    // TODO: This will affect windows below it.

    width = new_pos.x;
    height = new_pos.y;
    OFF_INTERNAL_FLAG(this, WINDOW_HEADER_VALIDATED);
    OFF_INTERNAL_FLAG(this, WINDOW_CONTENT_VALIDATED);
}
void sharp::window_base::set_window_rect(const int_rect& new_rect)
{
    // TODO: This will affect windows below it.

    posX = new_rect.left;
    posY = new_rect.top;
    width = new_rect.width;
    height = new_rect.height;
    OFF_INTERNAL_FLAG(this, WINDOW_HEADER_VALIDATED);
    OFF_INTERNAL_FLAG(this, WINDOW_CONTENT_VALIDATED);
}
void sharp::window_base::set_title(const std::string& new_title)
{
    title = new_title;
    OFF_INTERNAL_FLAG(this, WINDOW_HEADER_VALIDATED);
}

void sharp::window_base::invalidate()
{
    OFF_INTERNAL_FLAG(this, WINDOW_HEADER_VALIDATED);
    OFF_INTERNAL_FLAG(this, WINDOW_CONTENT_VALIDATED);
}

void sharp::window_base::hide()
{
    // TODO: This will affect the renderer

    OFF_INTERNAL_FLAG(this, WINDOW_VISIBLE);
}
void sharp::window_base::show()
{
    // TODO: This will affect the renderer

    ON_INTERNAL_FLAG(this, WINDOW_VISIBLE);
    OFF_INTERNAL_FLAG(this, WINDOW_HEADER_VALIDATED);
    OFF_INTERNAL_FLAG(this, WINDOW_CONTENT_VALIDATED);
}

const int2 sharp::window_base::to_screen(const int2& window_pos) const
{
    int header_height = get_header_height();
    if (header_height > 0) return int2(window_pos.x + posX, window_pos.y + posY + header_height + 1);
    else return int2(window_pos.x + posX, window_pos.y + posY);
}
const int2 sharp::window_base::to_window(const int2& screen_pos) const
{
    int header_height = get_header_height();
    if (header_height > 0) return int2(screen_pos.x - posX, screen_pos.y - posY - header_height - 1);
    else return int2(screen_pos.x - posY, screen_pos.y - posY);
}
