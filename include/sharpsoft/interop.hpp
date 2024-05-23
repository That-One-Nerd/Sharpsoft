#pragma once

#include "macros.hpp"

#ifdef SH_PROS_ACTIVE
#include "pros/rtos.hpp"
#else
#error Unsupported library. Interoperability cannot be used here.
#endif

namespace sharp
{
    class thread
    {
    private:
        void (*func)();
        bool active;

#ifdef SH_PROS_ACTIVE
        pros::Task* underlying;
#endif

    public:
        ~thread();
        thread(void (*function)());

        static void delay(int time_ms);

        bool is_active() const;

        void join();
        void start();
        void stop();
    };
}
