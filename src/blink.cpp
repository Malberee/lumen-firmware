#include "blink.h"
#include "modes.h"

void blink(CRGB color, int times)
{
  for (int i = 0; i < times; i++)
  {
    fill_solid(leds, NUM_LEDS, color);
    FastLED.delay(500);

    FastLED.clear();
    FastLED.delay(500);
  }
}