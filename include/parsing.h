#pragma once

#include "modes.h"
#include "params.h"

extern WiFiUDP udp;
extern char packetBuffer[255];

int split(char *str, char *ptrs[], char delimiter);
void parseParams(char *key, char *params);
void parseUDP();