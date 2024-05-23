#include "pros/rtos.hpp"
#include "sharpsoft/interop.hpp"

using namespace sharp;

bool thread::is_active() const
{
    return active;
}

#ifdef SH_PROS_ACTIVE
void thread::delay(int time_ms)
{
    pros::delay(time_ms);
}

thread::thread(void (*function)())
{
    active = false;
    func = function;
    underlying = nullptr;
}

thread::~thread()
{
    if (active) stop();
}

void thread::join()
{
    underlying->join();
}

void thread::start()
{
    if (active) return;

    underlying = new pros::Task(func);

    active = true;
}
void thread::stop()
{
    if (!active) return;

    underlying->remove();
    delete underlying;

    active = false;
}
#endif
