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
    width = size.y;
    flags = (window_flags)0;
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
const bool sharp::window_base::is_active() const
{
    return (flags & WINDOW_ACTIVE) > 0;
}

void sharp::window_base::set_pos(const int2& new_pos)
{
    // TODO: I'll have to re-render some parts.
    posX = new_pos.x;
    posY = new_pos.y;
}
void sharp::window_base::set_size(const int2& new_pos)
{
    // TODO: I'll have to re-render some parts.
    width = new_pos.x;
    height = new_pos.y;
}
void sharp::window_base::set_window_rect(const int_rect& new_rect)
{
    // TODO: I'll have to re-render some parts.
    posX = new_rect.left;
    posY = new_rect.top;
    width = new_rect.width;
    height = new_rect.height;
}
void sharp::window_base::set_title(const std::string& new_title)
{
    title = new_title;
}

void sharp::window_base::hide()
{
    // TODO: This will affect the renderer

    flags = (window_flags)(flags & ~WINDOW_ACTIVE);
}
void sharp::window_base::show()
{
    // TODO: This will affect the renderer

    flags = (window_flags)(flags | WINDOW_ACTIVE);
}
