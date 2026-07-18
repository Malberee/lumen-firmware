#include "websocket.h"
#include "parsing.h"
#include "blink.h"

WebSocketsServer ws(80);
int8_t activeClient = -1;

void onWebSocketEvent(
    uint8_t clientId,
    WStype_t type,
    uint8_t *payload,
    size_t length)
{
    switch (type)
    {
    case WStype_CONNECTED:
    {
        if (activeClient != -1 && activeClient != clientId)
        {
            ws.disconnect(activeClient);
        }

        activeClient = clientId;

        blink(SUCCESS_COLOR, 2);
        Serial.println("Client connected");

        break;
    }

    case WStype_DISCONNECTED:
        Serial.println("Client Disconnected");
        break;

    case WStype_TEXT:
    {
        payload[length] = '\0';
        parseMessage(clientId, (char *)payload);
        break;
    }

    default:
        break;
    }
}