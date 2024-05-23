#include "pros/rtos.hpp"
#define SHARPSOFT_INTERNAL

#include <string.h>
#include <vector>
#include "sharpsoft/global_misc.hpp"
#include "sharpsoft/internal.hpp"
#include "sharpsoft/interop.hpp"

using namespace sharp;
using std::vector;

const global_properties global_properties::defaults =
{
    0x95d9ed
};

bool init = false;
bool started = false;
color back_col;
thread* render_thread = nullptr;

vector<window_base*> windows;

void sharp::initialize()
{
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

void sharp::internal::render_iter()
{
    int window_count = windows.size();
    for (int i = 0; i < window_count; i++)
    {
        window_base* win = windows.at(i);
        win->paint();
    }
}
void sharp::internal::render_loop()
{
    while (true)
    {
        render_iter();
        thread::delay(100); // TODO: should be something else.
    }
}

void sharp::internal::add_window(window_base* win_ptr, size_t size)
{
    void* copy_raw = malloc(size);
    memcpy(copy_raw, (void*)(win_ptr), size);

    window_base* copy = (window_base*)copy_raw;
    windows.push_back(copy);
}

void sharp::start()
{
    if (!init || started) return;

    render_thread = new thread(internal::render_loop);
    render_thread->start();

    started = true;
}
void sharp::end()
{
    if (!init || !started) return;

    render_thread->stop();
    delete render_thread;

    started = false;
}

bool sharp::is_started()
{
    return started;
}
