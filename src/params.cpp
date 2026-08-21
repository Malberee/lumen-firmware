#include "params.h"
#include "modes.h"

Params::Params()
{
    colors.primary = CRGB::White;
    colors.secondary = CRGB::Black;
    frameInterval = 100;
    length = 3;
    power = true;
}

Colors Params::getColors()
{
    return colors;
}

void Params::setPrimary(const CRGB &color)
{
    this->colors.primary = color;
}

void Params::setSecondary(const CRGB &color)
{
    this->colors.secondary = color;
}

uint16_t Params::getFrameInterval()
{
    return frameInterval;
}
void Params::setFrameInterval(uint16_t frameInterval)
{
    if (frameInterval == 0)
    {
        frameInterval = 1;
    }

    this->frameInterval = frameInterval;
}

byte Params::getLength()
{
    return length;
}
void Params::setLength(uint16_t length)
{
    if (length == 0)
    {
        length = 1;
    }
    else if (length > NUM_LEDS)
    {
        length = NUM_LEDS;
    }

    this->length = length;
}

bool Params::getPower()
{
    return power;
}
void Params::setPower(bool power)
{
    this->power = power;

    if (power)
    {
        showCurrentMode();
    }
    else
    {
        FastLED.clear(true);
        FastLED.show();
    }
}

Params params;
