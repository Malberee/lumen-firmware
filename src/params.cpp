#include "params.h"
#include "modes.h"

Params::Params()
{
    colors.primary = CRGB::White;
    colors.secondary = CRGB::Black;
    speed = 100;
    length = 3;
    power = true;
}

Colors Params::getColors()
{
    return colors;
}

void Params::setPrimary(const char *color)
{
    CRGB parsed;
    if (!hexToCRGB(color, parsed))
    {
        return;
    }

    this->colors.primary = parsed;
}

void Params::setSecondary(const char *color)
{
    CRGB parsed;
    if (!hexToCRGB(color, parsed))
    {
        return;
    }

    this->colors.secondary = parsed;
}

uint16_t Params::getSpeed()
{
    return speed;
}
void Params::setSpeed(uint16_t speed)
{
    if (speed == 0)
    {
        speed = 1;
    }

    this->speed = speed;
}

byte Params::getLength()
{
    return length;
}
void Params::setLength(byte length)
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
