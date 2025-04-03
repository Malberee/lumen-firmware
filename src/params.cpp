#include "params.h"

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
    this->colors.primary = hexToCRGB(color);
}
void Params::setSecondary(const char *color)
{
    this->colors.secondary = hexToCRGB(color);
}

uint16_t Params::getSpeed()
{
    return speed;
}
void Params::setSpeed(uint16_t speed)
{
    this->speed = speed;
}

byte Params::getLength()
{
    return length;
}
void Params::setLength(byte length)
{
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
        modes[currentMode]->initial();
        FastLED.show();
    }
    else
    {
        FastLED.clear();
        FastLED.show();
    }
}

Params params;