#include "modes.h"

Chrome::Chrome() : BaseMode(5, 500)
{
    hue = 0;
};

void Chrome::initial()
{
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
}

void Chrome::tick()
{
    hue++;
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, 255));
}

Chrome chrome;