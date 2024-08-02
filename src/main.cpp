#include "main.h"
#include "sharpsoft/all.hpp"
#include "sharpsoft/basic_types.hpp"
#include "sharpsoft/windowing.hpp"

// This library is intended to be referenced by the prefix `sharp::`
// Including `using namespace sharp;` is not recommended.

class test_window : public sharp::window_base
{	
protected:
	void paint() override
	{
		
	}
	void tick() override
	{
		
	}

public:
    test_window() : window_base("Testing", sharp::int2(10, 10), sharp::int2(150, 100))
    {
		features().continuous_paint = true;
		features().continuous_tick = false;
		features().update_header = true;
    }
};

void initialize()
{
	// Initialize Sharpsoft.
	sharp::initialize();

	sharp::add_window(test_window());
	sharp::start();
}

void disabled() { }
void competition_initialize() { }
void autonomous() { }

void opcontrol()
{
	
}
