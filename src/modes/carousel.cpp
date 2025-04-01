#include "modes.h"
#include "utils.h"
#include "params.h"

void Carousel::initial()
{
    for(byte i = 0; i < NUM_LEDS; i++) {
        leds[i] = i % 2 ? params.getColors().primary : params.getColors().secondary; 
    }
}

void Carousel::tick()
{
    rotateLeds();
}

Carousel carousel;