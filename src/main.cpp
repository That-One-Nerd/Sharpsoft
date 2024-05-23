#include "main.h"
#include "sharpsoft/all.hpp"

// This library is intended to be referenced by the prefix `sharp::`
// Including `using namespace sharp;` is not recommended.

class test_window : public sharp::window_base
{	
protected:
	void paint() override
	{
		printf("Printed: %d\n", test_variable);
	}

public:
    test_window() : window_base("Testing", sharp::int2(10, 10), sharp::int2(150, 100))
    {
		
    }

	int test_variable;
};

void initialize()
{
	// Initialize Sharpsoft.
	sharp::initialize();

	test_window moment = test_window();
	moment.test_variable = 3;

	sharp::add_window(moment);
	sharp::start();
}

void disabled() { }
void competition_initialize() { }
void autonomous() { }

void opcontrol()
{
	
}
