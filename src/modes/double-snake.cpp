#include "modes.h"
#include "utils.h"
#include "params.h"

void DoubleSnake::initial()
{
    fillLeds(params.getColors().secondary);
    fillLeds(params.getColors().primary, 0, params.getLength() - 1);
    fillLeds(params.getColors().primary, NUM_LEDS / 2, NUM_LEDS / 2 + params.getLength() - 1);
}

void DoubleSnake::tick()
{
    rotateLeds();
}

DoubleSnake doubleSnake;