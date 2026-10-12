#include "blink.h"
#include "modes.h"
#include "params.h"

void blink(CRGB color, int times)
{
  for (int i = 0; i < times; i++)
  {
    fill_solid(leds, params.getLedCount(), color);
    FastLED.delay(500);

    FastLED.clear();
    FastLED.delay(500);
  }
}