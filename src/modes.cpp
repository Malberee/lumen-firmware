#include "modes.h"
#include "params.h"
#include "utils.h"

CRGB leds[NUM_LEDS];
BaseMode *modes[] = {&solid, &fade, &carousel, &snake, &doubleSnake, &fill, &doubleFill, &chroma, &rainbow};
Mode currentMode = SOLID;

unsigned long lastTime = 0;

void setCurrentMode(const char *mode)
{
    const char *modeNames[] = {"solid", "fade", "carousel", "snake", "double-snake", "fill", "double-fill", "chrome", "rainbow"};
    int8_t index = findIndex(modeNames, sizeof(modeNames) / sizeof(modeNames[0]), mode);
    
    if (index < 0) return;

    currentMode = static_cast<Mode>(index);
    showCurrentMode();
}

void showCurrentMode()
{
    modes[currentMode]->initial();
    if (params.getPower())
    {
        FastLED.show();
        FastLED.show(); // for some unknown reason color change does not work after the first call 🤷‍♂️
    }
}

void tick()
{
    if (currentMode != SOLID && params.getPower())
    {
        bool increaseSpeed = currentMode == FADE || currentMode == CHROMA || currentMode == RAINBOW;

        uint16_t interval = params.getSpeed() / (increaseSpeed ? 50 : 1);
        if (interval == 0)
        {
            interval = 1;
        }

        if (millis() - lastTime > interval)
        {
            lastTime = millis();
            modes[currentMode]->tick();
            FastLED.show();
        }
    }
}
