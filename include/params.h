#pragma once

#include "utils.h"

struct Colors
{
    CRGB primary;
    CRGB secondary;
};

class Params
{
    Colors colors;
    uint16_t speed;
    byte length;
    bool power;

public:
    Params();

    Colors getColors();
    void setPrimary(const char *color);
    void setSecondary(const char *color);

    uint16_t getSpeed();
    void setSpeed(uint16_t speed);

    byte getLength();
    void setLength(uint16_t length);

    bool getPower();
    void setPower(bool power);
};

extern Params params;
