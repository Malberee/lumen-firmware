#include "modes.h"
#include "params.h"

void Fill::initial()
{
    position = 0;
    reverse = false;
    fill_solid(leds, params.getLedCount(), params.getColors().secondary);
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

    if (position >= params.getLedCount() - 1)
    {
        reverse = !reverse;
        position = 0;
    }
    else
    {
        position++;
    }
}

Fill fill;
