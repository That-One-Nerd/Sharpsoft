#include "sharpsoft/global_misc.hpp"

using namespace sharp;

const global_properties global_properties::defaults =
{
    0x95d9ed
};

bool init = false;
bool started = false;
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
    if (started) sharp::end();

    // TODO

    init = false;
}

void sharp::re_initialize()
{
    bool restart = started;
    if (!init) return;
    uninitialize();
    initialize();
    if (restart) start();
}
void sharp::re_initialize(const global_properties& props)
{
    bool restart = started;
    if (!init) return;
    uninitialize();
    initialize();
    if (restart) start();
}

bool sharp::is_initialized()
{
    return init;
}

void sharp::start()
{
    if (!init || started) return;

    // TODO

    started = true;
}
void sharp::end()
{
    if (!init || !started) return;

    // TODO

    started = false;
}

bool sharp::is_started()
{
    return started;
}
