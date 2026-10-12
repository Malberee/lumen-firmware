#include "modes.h"
#include "utils.h"
#include "params.h"

Carousel::Carousel() : BaseMode(50, 2000)
{
}

void Carousel::initial()
{
    for (byte i = 0; i < params.getLedCount(); i++)
    {
        leds[i] = i % 2 ? params.getColors().primary : params.getColors().secondary;
    }
}

void Carousel::tick()
{
    rotateLeds();
}

Carousel carousel;