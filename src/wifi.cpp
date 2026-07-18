#include "wifi.h"
#include "blink.h"
#include "parsing.h"
#include "websocket.h"

bool isConnecting = false;

void onError(const char *error)
{
    isConnecting = false;

    ws.sendTXT(activeClient, error);

    blink(ERROR_COLOR, 2);
    setCurrentMode("solid");
    WiFi.mode(WIFI_AP);
}

void onConnect()
{
    isConnecting = false;

    ws.sendTXT(activeClient, WiFi.localIP().toString().c_str());

    blink(SUCCESS_COLOR, 2);
    setCurrentMode("solid");
    WiFi.mode(WIFI_STA);
}

void connectToWiFi(const char *ssid, const char *password)
{
    isConnecting = true;
    setCurrentMode("fade");
    WiFi.mode(WIFI_AP_STA);
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