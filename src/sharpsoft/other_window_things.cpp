#define SHARPSOFT_INTERNAL

#include "sharpsoft/windowing.hpp"

using namespace sharp;

const sharp::window_features sharp::window_features::defaults =
{
    false,
    true,
    false,
    true
};
const sharp::window_styles sharp::window_styles::defaults =
{
    0x000000,
    0xffffff,
    0x42b7ff,
    NORMAL
};

int sharp::get_header_height(size size)
{
    switch (size)
    {
        case SMALL:  return 16;
        case NORMAL: return 24;
        case LARGE:  return 32;

        default: return -1; // Unknown.
    }
}
