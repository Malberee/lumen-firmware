#include "modes.h"
#include "params.h"

void Solid::initial()
{
    fill_solid(leds, NUM_LEDS, params.getColors().primary);
}

Solid solid;