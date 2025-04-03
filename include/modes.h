#pragma once

#include "config.h"

enum Mode
{
    SOLID,
    FADE,
    CAROUSEL,
    SNAKE,
    DOUBLE_SNAKE,
    FILL,
    DOUBLE_FILL,
    CHROMA,
    RAINBOW
};

class BaseMode
{
public:
    virtual void initial() = 0;
    virtual void tick() {};
    virtual ~BaseMode() = default;
};

extern CRGB leds[NUM_LEDS];
extern BaseMode *modes[];
extern Mode currentMode;

#include "modes/fade.h"
#include "modes/carousel.h"
#include "modes/solid.h"
#include "modes/snake.h"
#include "modes/double-snake.h"
#include "modes/fill.h"
#include "modes/double-fill.h"
#include "modes/chroma.h"
#include "modes/rainbow.h"

void setCurrentMode(Mode mode);
void tick();