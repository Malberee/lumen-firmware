#include "modes.h"
#include "params.h"

#define MAX_BRIGHTNESS 100.0

Fade::Fade()
{
    brightness = MAX_BRIGHTNESS;
    increase = false;
}

void Fade::initial()
{
    fill_solid(leds, NUM_LEDS, params.getColors().primary);
}

void Fade::tick()
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

        brightness += 1;
    }
    else
    {
        brightness -= 1;
    }

    float scale = brightness / MAX_BRIGHTNESS;
    CRGB color = params.getColors().primary;

    fill_solid(leds, NUM_LEDS, CRGB(color.r * scale, color.g * scale, color.b * scale));
}

Fade fade;