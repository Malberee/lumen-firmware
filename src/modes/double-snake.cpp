#include "modes.h"
#include "utils.h"
#include "params.h"

void DoubleSnake::initial()
{
    byte length = params.getLength();
    if (length > NUM_LEDS / 2)
    {
        length = NUM_LEDS / 2;
    }

    fillLeds(params.getColors().secondary);
    fillLeds(params.getColors().primary, 0, length - 1);
    fillLeds(params.getColors().primary, NUM_LEDS / 2, NUM_LEDS / 2 + length - 1);
}

void DoubleSnake::tick()
{
    rotateLeds();
}

DoubleSnake doubleSnake;
