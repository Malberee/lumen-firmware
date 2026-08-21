#include "modes.h"

Rainbow::Rainbow() : BaseMode(5, 500)
{
    hue = 0;
}

void Rainbow::initial()
{
    fill_rainbow_circular(leds, NUM_LEDS, hue);
}

void Rainbow::tick()
{
    hue++;
    fill_rainbow_circular(leds, NUM_LEDS, hue);
}

Rainbow rainbow;