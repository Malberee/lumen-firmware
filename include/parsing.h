#pragma once

#include "modes.h"
#include "params.h"

constexpr size_t MAX_MESSAGE_LENGTH = 160;
constexpr byte MAX_PARAM_COUNT = 8;

void parseMessage(char* message);
