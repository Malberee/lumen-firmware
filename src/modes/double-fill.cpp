#include "modes.h"
#include "params.h"

DoubleFill::DoubleFill()
{
    position = 0;
    reverse = false;
}

void DoubleFill::initial()
{
    fill_solid(leds, NUM_LEDS, params.getColors().secondary);
}

void DoubleFill::tick()
{
    if (reverse)
    {
        leds[position] = params.getColors().secondary;
        leds[NUM_LEDS - 1 - position] = params.getColors().secondary;
    }
    else
    {
        leds[position] = params.getColors().primary;
        leds[NUM_LEDS - 1 - position] = params.getColors().primary;
    }

    if (position >= NUM_LEDS / 2 - 1)
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
