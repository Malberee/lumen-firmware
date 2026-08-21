#include "modes.h"

Chroma::Chroma() : BaseMode(5, 500)
{
    hue = 0;
};

void Chroma::initial()
{
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
}

void Chroma::tick()
{
    hue++;
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
}

Chroma chroma;