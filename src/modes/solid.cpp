#include "modes.h"
#include "params.h"

void Solid::initial()
{
    fill_solid(leds, params.getLedCount(), params.getColors().primary);
}

Solid solid;