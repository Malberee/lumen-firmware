#include "params.h"
#include "modes.h"
#include "gamma_table.h"

Params::Params()
{
    brightness = 128;
    colors.primary = CRGB::White;
    colors.secondary = CRGB::Black;
    frameInterval = 100;
    length = 3;
    power = true;
    ledCount = MIN_LEDS;
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
    else if (length > this->getLedCount())
    {
        length = this->getLedCount();
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
        showLeds();
    }
}

uint16_t Params::getLedCount()
{
    return ledCount;
}
void Params::setLedCount(uint16_t ledCount)
{
    if (ledCount < MIN_LEDS)
    {
        this->ledCount = MIN_LEDS;
    }
    else
    {
        this->ledCount = ledCount;
    }
};

byte Params::getBrightness()
{
    return gammaTable[brightness];
}

void Params::setBrightness(byte brightness)
{
    this->brightness = brightness;
}

Params params;
