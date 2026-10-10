#pragma once

#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

#define MIN_LEDS 2 // Do not touch this

#define MAX_LEDS 300
#define PIN 12

#define AP_SSID "Lumen"
#define AP_PASSWORD "12345678"

constexpr CRGB NEUTRAL_COLOR = CRGB(0, 111, 238);
constexpr CRGB SUCCESS_COLOR = CRGB(23, 201, 20);
constexpr CRGB ERROR_COLOR = CRGB(243, 5, 5);