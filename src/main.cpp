#include "main.h"
#include "sharpsoft/all.hpp"

// This library is intended to be referenced by the prefix `sharp::`
// Including `using namespace sharp;` is not recommended.

class test_window : public sharp::window_base
{	
protected:
	void paint() override
	{
		static int frame = 0;
		frame++;

		style() = 
		{
			sharp::color(frame % 256, 0, 0),
			sharp::color(0, 0, frame % 256)
		};
	}
	void tick() override
	{
		
	}

public:
    test_window() : window_base("Testing", sharp::int2(10, 10), sharp::int2(150, 100))
    {
		set_flag(sharp::CONTINUOUS_PAINT, true);
		set_flag(sharp::CONTINUOUS_TICK, false);
		set_flag(sharp::HEADER_UPDATE, true);
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
