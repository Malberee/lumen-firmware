#include "modes.h"
#include "utils.h"
#include "params.h"

void DoubleSnake::initial()
{
    byte length = params.getLength();
    uint16_t ledCount = params.getLedCount();
    Colors colors = params.getColors();

    if (length > ledCount / 2)
    {
        length = ledCount / 2;
    }

    fillLeds(colors.secondary);
    fillLeds(colors.primary, 0, length - 1);
    fillLeds(colors.primary, ledCount / 2, ledCount / 2 + length - 1);
}

void DoubleSnake::tick()
{
    rotateLeds();
}

DoubleSnake doubleSnake;
