#include "modes.h"
#include "params.h"

Rainbow::Rainbow() : BaseMode(5, 500)
{
    hue = 0;
}

void Rainbow::initial()
{
    fill_rainbow_circular(leds, params.getLedCount(), hue);
}

void Rainbow::tick()
{
    hue++;
    fill_rainbow_circular(leds, params.getLedCount(), hue);
}

Rainbow rainbow;