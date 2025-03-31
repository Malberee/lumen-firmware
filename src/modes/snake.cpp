#include "modes.h"
#include "utils.h"
#include "params.h"

void Snake::initial()
{
    fillLeds(params.getColors().secondary);
    fillLeds(params.getColors().primary, 0, params.getLength() - 1);
}

void Snake::tick()
{
    rotateLeds();
}

Snake snake;