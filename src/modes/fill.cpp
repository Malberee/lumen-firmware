#include "modes.h"
#include "params.h"

Fill::Fill()
{
    position = 0;
    reverse = false;
}

void Fill::initial()
{
    fill_solid(leds, NUM_LEDS, params.getColors().secondary);
}

void Fill::tick()
{
    if (reverse)
    {
        leds[position] = params.getColors().secondary;
    }
    else
    {
        leds[position] = params.getColors().primary;
    }

    if (position >= NUM_LEDS - 1)
    {
        reverse = !reverse;
        position = 0;
    } else {
        position++;
    }
}

Fill fill;
