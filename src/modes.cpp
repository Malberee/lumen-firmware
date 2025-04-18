#include "modes.h"
#include "params.h"
#include "utils.h"

CRGB leds[NUM_LEDS];
BaseMode *modes[] = {&solid, &fade, &carousel, &snake, &doubleSnake, &fill, &doubleFill, &chroma, &rainbow};
Mode currentMode = SOLID;

void setCurrentMode(char *mode)
{
    const char *modeNames[] = {"solid", "fade", "carousel", "snake", "double-snake", "fill", "double-fill", "chroma", "rainbow"};
    byte index = findIndex(modeNames, sizeof(modeNames), mode);

    currentMode = static_cast<Mode>(index);
    modes[currentMode]->initial();
    if (params.getPower())
    {
        FastLED.show();
    }
}

void tick()
{
    if (currentMode != SOLID && params.getPower())
    {
        bool increaseSpeed = currentMode == FADE || currentMode == CHROMA || currentMode == RAINBOW;

        EVERY_N_MILLISECONDS_DYNAMIC(params.getSpeed() / (increaseSpeed ? 50 : 1))
        {
            modes[currentMode]->tick();
            FastLED.show();
        }
    }
}