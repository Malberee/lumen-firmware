#pragma once

#include "modes.h"

void fillLeds(CRGB color, byte start = 0, byte end = NUM_LEDS - 1);
void rotateLeds();
CRGB hexToCRGB(const char *hex);
byte findIndex(const char *arr[], int size, const char *target);