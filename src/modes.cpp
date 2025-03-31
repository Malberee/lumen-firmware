#include "modes.h"
#include "params.h"

bool isOff = false;
CRGB leds[NUM_LEDS];
BaseMode *modes[] = {&solid, &fade, &snake, &doubleSnake, &fill, &doubleFill};
Mode currentMode = DOUBLE_FILL;

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
        EVERY_N_MILLISECONDS_DYNAMIC(currentMode == FADE ? params.getSpeed() / 10 : params.getSpeed())
        {
            modes[currentMode]->tick();
            FastLED.show();
        }
    }
}