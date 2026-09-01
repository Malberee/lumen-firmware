#include "wifi.h"
#include "blink.h"
#include "parsing.h"
#include "websocket.h"

bool isConnecting = false;
static Mode lastMode = currentMode;

static void sendLocalIpToActiveClient()
{
    IPAddress ip = WiFi.localIP();
    char ipText[16];
    snprintf(
        ipText,
        sizeof(ipText),
        "%u.%u.%u.%u",
        ip[0],
        ip[1],
        ip[2],
        ip[3]);

    Serial.println(ipText);

    sendToActiveClient(ipText);
}

void onError(const char *error)
{
    isConnecting = false;
    currentMode = static_cast<Mode>(lastMode);

    sendToActiveClient(error);

    blink(ERROR_COLOR, 2);
    showCurrentMode();
    WiFi.mode(WIFI_AP);
}

void onConnect()
{

    isConnecting = false;
    currentMode = static_cast<Mode>(lastMode);

    sendLocalIpToActiveClient();
    ws.disconnect(activeClient);
    
    blink(SUCCESS_COLOR, 2);
    showCurrentMode();

    WiFi.mode(WIFI_STA);
}

void connectToWiFi(const char *ssid, const char *password)
{
    if (!ssid || !password)
    {
        return;
    }

    isConnecting = true;
    lastMode = currentMode;

    setCurrentMode("breathing");

    WiFi.mode(WIFI_AP_STA);
    WiFi.disconnect();
    WiFi.begin(ssid, password);
}

void tickConnection()
{
    const wl_status_t status = WiFi.status();

    switch (status)
    {
    case WL_CONNECTED:
        onConnect();
        break;
    case WL_CONNECT_FAILED:
        onError("ConnectFailed");
        break;
    case WL_WRONG_PASSWORD:
        onError("WrongPassword");
        break;
    case WL_NO_SSID_AVAIL:
        onError("NetworkNotFound");
        break;
    default:
        break;
    }
}
