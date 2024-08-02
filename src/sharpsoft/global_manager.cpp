#define SHARPSOFT_INTERNAL

#include <string.h>
#include <vector>
#include "sharpsoft/global_misc.hpp"
#include "sharpsoft/internal.hpp"
#include "sharpsoft/interop.hpp"
#include "sharpsoft/windowing.hpp"

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

    // Dispose of all windows.
    for (int i = 0; i < windows.size(); i++)
    {
        delete windows.at(i);
    }
    windows.clear();

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
        // TODO: if the window is null, display an error?

        // Now tick the window if applicable.
        if (win->win_features.continuous_tick) win->tick();

        // Apply any possible invalidations.
        if (win->win_features.continuous_paint)
        {
            OFF_INTERNAL_FLAG(win, WINDOW_CONTENT_VALIDATED);
        }

        // Now render anything that is invalidated.
        // If the header is set to sync with the content validation, render it
        // regardless of if it would otherwise.
        if (!HAS_INTERNAL_FLAG(win, WINDOW_HEADER_VALIDATED) ||
            (!HAS_INTERNAL_FLAG(win, WINDOW_CONTENT_VALIDATED) && win->win_features.update_header))
        {
            win->paint_header();
            ON_INTERNAL_FLAG(win, WINDOW_HEADER_VALIDATED);
        }
        if (!HAS_INTERNAL_FLAG(win, WINDOW_CONTENT_VALIDATED))
        {
            win->paint_content_back();
            win->paint();
            ON_INTERNAL_FLAG(win, WINDOW_CONTENT_VALIDATED);
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
    // Make copy of window so it remains in scope.
    // There must be a better way to do this, but I don't know it.
    // If you don't do this, then if windows are created in a method,
    // then when that scope is terminated, a null pointer is created.
    // However, when a copy is made, from that point onward the original
    // in the method no longer affects the copy.
    
    // Maybe instead a reference could be added to the original pointer
    // to prevent it going out of scope with shared_ptr? Don't know,
    // never used it.

    void* copy_raw = malloc(size);
    memcpy(copy_raw, (void*)(win_ptr), size);

    window_base* copy = (window_base*)copy_raw;
    windows.push_back(copy);
    ON_INTERNAL_FLAG(copy, WINDOW_ACTIVE);
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
