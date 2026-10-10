#include "config.h"
#include "modes.h"
#include "parsing.h"
#include "wifi.h"
#include "blink.h"
#include "websocket.h"

void setup()
{
  Serial.begin(115200);

  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);

  ws.begin();
  ws.onEvent(onWebSocketEvent);

  controller = &FastLED.addLeds<NEOPIXEL, PIN>(leds, MAX_LEDS);

  blink(NEUTRAL_COLOR, 2);
  showCurrentMode();
}

void loop()
{
  tick();
  ws.loop();

  if (isConnecting)
  {
    tickConnection();
  }
}
