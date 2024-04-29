#include "sharpsoft/global_misc.hpp"

using namespace sharp;

const global_properties global_properties::defaults = { }; // TODO

bool initialized = false;

void sharp::initialize()
{
    if (initialized) return;
    initialize(global_properties::defaults);
}
void sharp::initialize(const global_properties& flags)
{
    if (initialized) return;

    // TODO
    
    initialized = true;
}

void sharp::uninitialize()
{
    if (!initialized) return;

    // TODO

    initialized = false;
}

void sharp::re_initialize()
{
    if (!initialized) return;
    uninitialize();
    initialize();
}
void sharp::re_initialize(const global_properties& flags)
{
    if (!initialized) return;
    uninitialize();
    initialize();
}

bool sharp::is_initialized()
{
    return initialized;
}
