#define SHARPSOFT_INTERNAL

#include <string.h>
#include <vector>
#include "sharpsoft/enums.hpp"
#include "sharpsoft/global_misc.hpp"
#include "sharpsoft/internal.hpp"
#include "sharpsoft/interop.hpp"

using namespace sharp;
using std::vector;

const global_properties global_properties::defaults =
{
    0x95d9ed,
    20,
};

bool init = false;
bool started = false;
color back_col;
int render_wait_ms;
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
    render_wait_ms = 1000 / props.refresh_rate;
    
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

    // The way windows are ordered in the vector represents
    // the rendering order. More recent pushes (so further
    // down the list) have a higher order.
    for (int i = 0; i < window_count; i++)
    {
        window_base* win = windows.at(i);
        // First handle special stuff.

        // Now tick the window if applicable.
        if (HAS_WINDOW_FLAG(win, CONTINUOUS_TICK)) win->tick();

        // Apply any possible invalidations.
        if (HAS_WINDOW_FLAG(win, CONTINUOUS_PAINT)) win->content_validated = false;

        // Now render anything that is invalidated.
        if (!win->content_validated)
        {
            win->paint();
            win->content_validated = true;
        }
        if (!win->header_validated)
        {
            win->paint_header();
            win->header_validated = true;
        }
    }
}
void sharp::internal::render_loop()
{
    thread::delay(50); // Wait a sec for the screen to be ready.
    while (true)
    {
        render_iter();
        thread::delay(render_wait_ms);
    }
}

void sharp::internal::add_window(window_base* win_ptr, size_t size)
{
    void* copy_raw = malloc(size);
    memcpy(copy_raw, (void*)(win_ptr), size);

    window_base* copy = (window_base*)copy_raw;
    windows.push_back(copy);
    copy->active = true;
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
