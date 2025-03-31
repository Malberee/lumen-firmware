#pragma once 

#include "modes.h"

void fillLeds(CRGB color, byte start = 0, byte end = NUM_LEDS - 1);
void rotateLeds();
CRGB hexToCRGB(const char* hex);