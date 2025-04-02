#include "config.h"
#include "modes.h"
#include "parsing.h"
#include "wifi.h"
#include "blink.h"

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);

  udp.begin(8888);

  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  blink(NEUTRAL_COLOR, 2);
  modes[currentMode]->initial();
  FastLED.show();
}

void loop()
{
  tick();
  parseUDP();
  if (isConnecting)
  {
    tickConnection();
  }
}