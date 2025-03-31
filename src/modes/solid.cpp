#include "modes.h"
#include "params.h"

void Solid::initial() {
    Serial.print(params.getColors().primary.toString().c_str());

    fill_solid(leds, NUM_LEDS, params.getColors().primary);
}

Solid solid;