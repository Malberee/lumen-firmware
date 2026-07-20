#pragma once

#include "modes.h"

void fillLeds(CRGB color, byte start = 0, byte end = NUM_LEDS - 1);
void rotateLeds();
bool hexToCRGB(const char *hex, CRGB &color);
int8_t findIndex(const char* arr[], size_t size, const char* target);
