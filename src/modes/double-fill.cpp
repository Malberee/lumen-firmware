#include "modes.h"
#include "params.h"

void DoubleFill::initial()
{
    position = 0;
    reverse = false;
    fill_solid(leds, params.getLedCount(), params.getColors().secondary);
}

void DoubleFill::tick()
{
    uint16_t ledCount = params.getLedCount();

    if (reverse)
    {
        leds[position] = params.getColors().secondary;
        leds[ledCount - 1 - position] = params.getColors().secondary;
    }
    else
    {
        leds[position] = params.getColors().primary;
        leds[ledCount - 1 - position] = params.getColors().primary;
    }

    if (position >= ledCount / 2 - 1)
    {
        reverse = !reverse;
        position = 0;
    }
    else
    {
        position++;
    }
}

DoubleFill doubleFill;
