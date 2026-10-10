#pragma once

#include "utils.h"

struct Colors
{
    CRGB primary;
    CRGB secondary;
};

class Params
{
    uint16_t ledCount;
    Colors colors;
    uint16_t frameInterval;
    byte length;
    byte brightness;
    bool power;

public:
    Params();

    uint16_t getLedCount();
    void setLedCount(uint16_t frameInterval);

    Colors getColors();
    void setPrimary(const CRGB &color);
    void setSecondary(const CRGB &color);

    uint16_t getFrameInterval();
    void setFrameInterval(uint16_t frameInterval);

    byte getBrightness();
    void setBrightness(byte brightness);

    byte getLength();
    void setLength(uint16_t length);

    bool getPower();
    void setPower(bool power);
};

extern Params params;
