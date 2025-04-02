#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define NUM_LEDS 24
#define PIN 4

#define AP_SSID "NodeMCU Lumen"
#define AP_PASSWORD "12345678"

constexpr CRGB NEUTRAL_COLOR = CRGB(0, 111, 238);
constexpr CRGB SUCCESS_COLOR = CRGB(23, 201, 20);
constexpr CRGB ERROR_COLOR = CRGB(243, 5, 5);