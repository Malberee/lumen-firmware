#include "modes.h"
#include "params.h"
#include "gamma_table.h"

Breathing::Breathing() : BaseMode(1, 50)
{
}

void Breathing::initial()
{
    brightness = 0;
    increasing = true;

    CRGB color = params.getColors().primary;
    color.nscale8(gammaTable[brightness]);

    fill_solid(leds, NUM_LEDS, color);
}

void Breathing::tick()
{
    if (increasing)
    {
        if (brightness == 255)
        {
            increasing = false;
            brightness--;
        }
        else
        {
            brightness++;
        }
    }
    else
    {
        if (brightness == 0)
        {
            increasing = true;
            brightness++;
        }
        else
        {
            brightness--;
        }
    }

    CRGB color = params.getColors().primary;
    color.nscale8(gammaTable[brightness]);

    fill_solid(leds, NUM_LEDS, color);
}

Breathing breathing;