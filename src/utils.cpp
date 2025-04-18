#include "utils.h"

void fillLeds(CRGB color, byte start, byte end)
{
  for (int i = start; i <= end; i++)
  {
    leds[i] = color;
  }
}

void rotateLeds()
{
  CRGB lastElement = leds[NUM_LEDS - 1];

  for (size_t i = NUM_LEDS - 1; i > 0; i--)
  {
    leds[i] = leds[i - 1];
  }

  leds[0] = lastElement;
}

CRGB hexToCRGB(const char *hex)
{
  int r, g, b;
  if (hex[0] == '#')
  {
    hex++;
  }
  sscanf(hex, "%02x%02x%02x", &r, &g, &b);
  return CRGB(r, g, b);
}

byte findIndex(const char* arr[], byte size, const char* target) {
    for (byte i = 0; i < size; ++i) {
        if (strcmp(arr[i], target) == 0) {
            return i;
        }
    }
    return -1;
}