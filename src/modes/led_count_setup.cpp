#include "modes.h"
#include "params.h"

void LedCountSetup::initial()
{
    uint16_t ledCount = params.getLedCount();

    controller->clearLeds();
    fill_solid(leds, ledCount, CRGB::White);
    leds[ledCount - 1] = CRGB::Red;
}

LedCountSetup ledCountSetup;