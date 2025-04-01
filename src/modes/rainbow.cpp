#include "modes.h"

Rainbow::Rainbow()
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