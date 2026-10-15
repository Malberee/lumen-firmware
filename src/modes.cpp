#include "modes.h"
#include "params.h"
#include "utils.h"

CRGB leds[MAX_LEDS];
BaseMode *modes[] = {&solid, &breathing, &carousel, &snake, &doubleSnake, &fill, &doubleFill, &chrome, &rainbow, &ledCountSetup};
Mode currentMode = SOLID;
CLEDController *controller;

uint16_t BaseMode::getMinFrameInterval() const
{
    return minFrameInterval;
}

uint16_t BaseMode::getMaxFrameInterval() const
{
    return maxFrameInterval;
}

unsigned long lastTime = 0;

void setCurrentMode(const char *mode)
{
    const char *modeNames[] = {"solid", "breathing", "carousel", "snake", "double-snake", "fill", "double-fill", "chrome", "rainbow", "led-count-setup"};
    int8_t index = findIndex(modeNames, sizeof(modeNames) / sizeof(modeNames[0]), mode);

    if (index < 0)
        return;

    currentMode = static_cast<Mode>(index);
    showCurrentMode();
}

void showCurrentMode()
{
    modes[currentMode]->initial();
    if (params.getPower())
    {
        showLeds();
        showLeds(); // for some unknown reason color change does not work after the first call 🤷‍♂️
    }
}

void tick()
{
    if (currentMode != SOLID && params.getPower())
    {

        uint16_t interval = params.getFrameInterval();

        if (millis() - lastTime > interval)
        {
            lastTime = millis();
            modes[currentMode]->tick();
            showLeds();
        }
    }
}
