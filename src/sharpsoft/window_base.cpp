#include "enums.hpp"
#include "sharpsoft/window_types.hpp"

using std::string;
using namespace sharp;

sharp::window_base::window_base(const string& title, const int2& pos, const int2& size)
{
    this->title = title;
    posX = pos.x;
    posY = pos.y;
    width = size.x;
    height = size.y;
    flags = (window_flags)0;
    active = false;
    visible = true;

    header_validated = false;
    content_validated = false;
}

bool sharp::window_base::get_flag(window_flags flag) const
{
    return (flags & flag) > 0;
}
const int2 sharp::window_base::get_pos() const
{
    return int2(posX, posY);
}
const int2 sharp::window_base::get_size() const
{
    return int2(width, height);
}
const int_rect sharp::window_base::get_window_rect() const
{
    return int_rect(posX, posY, width, height);
}
const string sharp::window_base::get_title() const
{
    return title;
}
bool sharp::window_base::is_active() const
{
    return active;
}
bool sharp::window_base::is_visible() const
{
    return visible;
}

void sharp::window_base::set_flag(window_flags flag, bool value)
{
    switch (flag)
    {
        case CONTINUOUS_PAINT:
        case CONTINUOUS_TICK:
            break; // No invalidation.
    }

    if (value) flags = (window_flags)(flags | flag);
    else flags = (window_flags)(flags & ~flag);
}
void sharp::window_base::set_pos(const int2& new_pos)
{
    // TODO: This will affect windows below it.

    posX = new_pos.x;
    posY = new_pos.y;    
    header_validated = false;
    content_validated = false;
}
void sharp::window_base::set_size(const int2& new_pos)
{
    // TODO: This will affect windows below it.

    width = new_pos.x;
    height = new_pos.y;
    header_validated = false;
    content_validated = false;
}
void sharp::window_base::set_window_rect(const int_rect& new_rect)
{
    // TODO: This will affect windows below it.

    posX = new_rect.left;
    posY = new_rect.top;
    width = new_rect.width;
    height = new_rect.height;
    header_validated = false;
    content_validated = false;
}
void sharp::window_base::set_title(const std::string& new_title)
{
    title = new_title;
    header_validated = false;
}

void sharp::window_base::invalidate()
{
    header_validated = false;
    content_validated = false;
}

void sharp::window_base::hide()
{
    // TODO: This will affect the renderer

    visible = false;
}
void sharp::window_base::show()
{
    // TODO: This will affect the renderer

    visible = true;
    header_validated = false;
    content_validated = false;
}
