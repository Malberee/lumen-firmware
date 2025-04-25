#include "modes.h"
#include "params.h"
#include "utils.h"

CRGB leds[NUM_LEDS];
BaseMode *modes[] = {&solid, &fade, &carousel, &snake, &doubleSnake, &fill, &doubleFill, &chroma, &rainbow};
Mode currentMode = SOLID;

unsigned long lastTime = 0;

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

        if (millis() - lastTime > (params.getSpeed() / (increaseSpeed ? 50 : 1)))
        {
            lastTime = millis();
            modes[currentMode]->tick();
            FastLED.show();
        }
    }
}