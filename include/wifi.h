#pragma once

#include "modes.h"

extern bool isConnecting;

void onError(const char *error);
void onConnect();
void connectToWiFi(const char *ssid, const char *password);
void tickConnection();