#include "websocket.h"
#include "parsing.h"
#include "blink.h"

WebSocketsServer ws(80);
int8_t activeClient = -1;

static bool hasActiveClient()
{
    return activeClient >= 0 && ws.clientIsConnected(static_cast<uint8_t>(activeClient));
}

void sendToActiveClient(const char *message)
{
    if (!hasActiveClient())
    {
        return;
    }

    ws.sendTXT(activeClient, message);
}

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

        Serial.println("Client connected");

        break;
    }

    case WStype_DISCONNECTED:
        if (activeClient == clientId)
        {
            activeClient = -1;
        }
        Serial.println("Client Disconnected");
        break;

    case WStype_TEXT:
    {
        if (length == 0 || length > MAX_MESSAGE_LENGTH)
        {
            Serial.println("Rejected oversized or empty message");
            break;
        }

        char message[MAX_MESSAGE_LENGTH + 1];
        memcpy(message, payload, length);
        message[length] = '\0';
        parseMessage(message);
        break;
    }

    default:
        break;
    }
}
