#pragma once

#include "modes.h"

void fillLeds(CRGB color, byte start = 0, byte end = NUM_LEDS - 1);
void rotateLeds();
CRGB hexToCRGB(const char *hex);
int8_t findIndex(const char* arr[], int8_t size, const char* target);