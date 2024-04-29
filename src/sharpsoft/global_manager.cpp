#include "sharpsoft/global_misc.hpp"

using namespace sharp;

const global_properties global_properties::defaults =
{
    0x95d9ed
};

bool init = false;
color back_col;

void sharp::initialize()
{
    if (init) return;
    sharp::initialize(global_properties::defaults);
}
void sharp::initialize(const global_properties& props)
{
    if (init) return;

    back_col = props.background_color;
    
    init = true;
}

void sharp::uninitialize()
{
    if (!init) return;

    // TODO

    init = false;
}

void sharp::re_initialize()
{
    if (!init) return;
    uninitialize();
    initialize();
}
void sharp::re_initialize(const global_properties& props)
{
    if (!init) return;
    uninitialize();
    initialize();
}

bool sharp::is_initialized()
{
    return init;
}
