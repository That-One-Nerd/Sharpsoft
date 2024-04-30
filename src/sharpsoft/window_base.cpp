#include "sharpsoft/window_types.hpp"

using namespace sharp;

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

void sharp::window_base::set_pos(const int2 &new_pos)
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
void sharp::window_base::set_window_rect(const int_rect &new_rect)
{
    // TODO: I'll have to re-render some parts.
    posX = new_rect.left;
    posY = new_rect.top;
    width = new_rect.width;
    height = new_rect.height;
}
