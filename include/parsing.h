#pragma once

#include "modes.h"
#include "params.h"

int split(char *str, char *ptrs[], char delimiter);
void parseParams(char *key, char *params);
void parseMessage(uint8_t clientId, char* message);