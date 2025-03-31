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

public:
    Params();

    Colors getColors();
    void setPrimary(const char* color);
    void setSecondary(const char* color);

    uint16_t getSpeed();
    void setSpeed(uint16_t speed);

    byte getLength();
    void setLength(byte length);
};

extern Params params;