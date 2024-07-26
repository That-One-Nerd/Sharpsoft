#define SHARPSOFT_INTERNAL

#include "sharpsoft/internal.hpp"
#include "sharpsoft/windowing.hpp"

using namespace sharp;

const sharp::window_styles sharp::window_styles::defaults =
{
    color(0, 0, 0),
    color(255, 255, 255)
};

bool sharp::windows_intersect(const window_base& winA, const window_base& winB)
{
    // TODO: When I finish the header this'll change.
    int winAMinX = winA.posX - 1, winAMaxX = winA.posX + winA.width + 2,
        winAMinY = winA.posY - 1, winAMaxY = winA.posY + winA.height + 2,
        winBMinX = winB.posX - 1, winBMaxX = winB.posX + winB.width + 2,
        winBMinY = winB.posY - 1, winBMaxY = winB.posY + winB.height + 2;

    // Killer IF statement but it works.
    return (winAMinX >= winBMinX && winAMinX <= winBMaxX) || // winAMinX within winB
           (winAMinY >= winBMinY && winAMinY <= winBMaxY) || // winAMinY within winB
           (winAMaxX >= winBMinX && winAMaxX <= winBMaxX) || // winAMaxX within winB
           (winAMaxY >= winBMinY && winAMaxY <= winBMaxY) || // winAMaxY within winB
           (winBMinX >= winAMinX && winBMinX <= winAMaxX) || // winBMinX within winA
           (winBMinY >= winAMinY && winBMinY <= winAMaxY) || // winBMinY within winA
           (winBMaxX >= winAMinX && winBMaxX <= winAMaxX) || // winBMaxX within winA
           (winBMaxY >= winAMinY && winBMaxY <= winAMaxY);
}
