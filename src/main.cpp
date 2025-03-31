#include "config.h"
#include "modes.h"

void setup()
{
  Serial.begin(115200);

  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  modes[currentMode]->initial();
}

void loop()
{
  tick();
}