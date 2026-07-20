#pragma once

#include "config.h"

extern WebSocketsServer ws;
extern int8_t activeClient;

void sendToActiveClient(const char *message);

void onWebSocketEvent(
    uint8_t clientId,
    WStype_t type,
    uint8_t* payload,
    size_t length
);
