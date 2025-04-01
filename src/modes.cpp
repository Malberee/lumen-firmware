#include "modes.h"
#include "params.h"

bool isOff = false;
CRGB leds[NUM_LEDS];
BaseMode *modes[] = {&solid, &fade, &carousel, &snake, &doubleSnake, &fill, &doubleFill, &chroma, &rainbow};
Mode currentMode = CAROUSEL;

void setCurrentMode(Mode mode)
{
    currentMode = mode;
    modes[currentMode]->initial();
    FastLED.show();
}

void tick()
{
    if (currentMode != SOLID || isOff)
    {
        bool increaseSpeed = currentMode == FADE || currentMode == CHROMA || currentMode == RAINBOW;

        EVERY_N_MILLISECONDS_DYNAMIC(params.getSpeed() / (increaseSpeed ? 50 : 1))
        {
            modes[currentMode]->tick();
            FastLED.show();
        }
    }
}