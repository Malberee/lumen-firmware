#include "modes.h"
#include "params.h"

bool isOff = false;
CRGB leds[NUM_LEDS];
BaseMode *modes[] = {&solid, &fade, &snake, &doubleSnake, &fill, &doubleFill, &chroma};
Mode currentMode = CHROMA;

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
        bool increaseSpeed = currentMode == FADE || currentMode == CHROMA;

        EVERY_N_MILLISECONDS_DYNAMIC(params.getSpeed() / (increaseSpeed ? 50 : 1))
        {
            modes[currentMode]->tick();
            FastLED.show();
        }
    }
}