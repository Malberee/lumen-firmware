#include "modes.h"
#include "params.h"

#define MAX_BRIGHTNESS 100.0

Breathing::Breathing() : BaseMode(5, 500)
{
    brightness = MAX_BRIGHTNESS;
    increase = false;
}

void Breathing::initial()
{
    fill_solid(leds, NUM_LEDS, params.getColors().primary);
}

void Breathing::tick()
{
    if (brightness >= MAX_BRIGHTNESS)
    {
        increase = false;
    }
    else if (brightness <= 0)
    {
        increase = true;
    }

    if (increase)
    {

        brightness++;
    }
    else
    {
        brightness--;
    }

    float scale = brightness / MAX_BRIGHTNESS;
    CRGB color = params.getColors().primary;

    fill_solid(leds, NUM_LEDS, CRGB(color.r * scale, color.g * scale, color.b * scale));
}

Breathing breathing;