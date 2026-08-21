#pragma once

#include "modes.h"

void fillLeds(CRGB color, byte start = 0, byte end = NUM_LEDS - 1);
void rotateLeds();
int8_t findIndex(const char *arr[], size_t size, const char *target);
int splitString(char *str, char *ptrs[], byte capacity, char delimiter);
bool parseUint16(const char *str, uint16_t &value);
bool parseUint8(const char *str, uint8_t &value);
uint16_t clamp(uint16_t value, uint16_t min, uint16_t max);
bool isValidLength(const char *value, byte minLength, byte maxLength);
float speedToInterval(uint8_t speed, float minInterval, float maxInterval);