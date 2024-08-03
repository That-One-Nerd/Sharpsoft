#include <numbers>
#include "main.h"
#include "sharpsoft/all.hpp"
#include "sharpsoft/basic_types.hpp"
#include "sharpsoft/windowing.hpp"

// This library is intended to be referenced by the prefix `sharp::`
// Including `using namespace sharp;` is not recommended.

using std::numbers::pi;

class test_window : public sharp::window_base
{
protected:
	void paint() override
	{
		constexpr int points = 5;

		int bigRadius = 100,
			smallRadius = 60;

		sharp::int2 center = get_size() / 2;
		sharp::int2 arr[points * 2];

		double time = get_elapsed_time();
		double offset = pi / points;

		for (int i = 0; i < points; i++)
		{
			arr[i * 2] = sharp::int2(bigRadius * cos(time + (offset * i * 2)), bigRadius * sin(time + (offset * i * 2))) + center;
			arr[i * 2 + 1] = sharp::int2(smallRadius * cos(time + (offset * (i * 2 + 1))), smallRadius * sin(time + (offset * (i * 2 + 1)))) + center;
		}

		for (int i = 0; i < points * 2; i++)
		{
			sharp::int2& this_point = arr[i],
						 next_point = arr[(i + 1) % (points * 2)];
			draw_line(0xABCDEF, this_point, next_point);
		}
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
