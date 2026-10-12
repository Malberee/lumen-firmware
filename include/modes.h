#pragma once

#include "config.h"

enum Mode
{
    SOLID,
    BREATHING,
    CAROUSEL,
    SNAKE,
    DOUBLE_SNAKE,
    FILL,
    DOUBLE_FILL,
    CHROME,
    RAINBOW,
    LED_COUNT_SETUP
};

class BaseMode
{
public:
    BaseMode(
        uint16_t minFrameInterval = 10,
        uint16_t maxFrameInterval = 1000)
        : minFrameInterval(minFrameInterval),
          maxFrameInterval(maxFrameInterval)
    {
    }

    virtual void initial() = 0;
    virtual void tick() {};
    virtual ~BaseMode() = default;

    uint16_t getMinFrameInterval() const;
    uint16_t getMaxFrameInterval() const;

protected:
    uint16_t minFrameInterval;
    uint16_t maxFrameInterval;
};

extern CRGB leds[MAX_LEDS];
extern BaseMode *modes[];
extern Mode currentMode;
extern CLEDController *controller;

#include "modes/breathing.h"
#include "modes/carousel.h"
#include "modes/solid.h"
#include "modes/snake.h"
#include "modes/double-snake.h"
#include "modes/fill.h"
#include "modes/double-fill.h"
#include "modes/chrome.h"
#include "modes/rainbow.h"
#include "modes/led_count_setup.h"

extern unsigned long lastTime;

void setCurrentMode(const char *mode);
void showCurrentMode();
void tick();
