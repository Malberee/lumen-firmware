#include "parsing.h"
#include "wifi.h"
#include "params.h"
#include "blink.h"
#include "utils.h"
#include "modes.h"

struct ParsedParam
{
    char *key;
    char *value;
};

static int parseParamPairs(char *value, ParsedParam params[], byte capacity)
{
    char *parts[MAX_PARAM_COUNT];
    int count = splitString(value, parts, capacity, ';');
    if (count <= 0)
    {
        return -1;
    }

    for (int i = 0; i < count; i++)
    {
        char *pair[2];
        int pairCount = splitString(parts[i], pair, 2, '=');
        if (pairCount != 2 || pair[0][0] == '\0')
        {
            return -1;
        }

        params[i].key = pair[0];
        params[i].value = pair[1];
    }

    return count;
}

static bool parseRGB(char *str, CRGB &color)
{
    if (!str)
    {
        return false;
    }

    char *parts[3];
    if (splitString(str, parts, 3, ',') != 3)
    {
        return false;
    }

    uint8_t r, g, b;

    if (!parseUint8(parts[0], r) ||
        !parseUint8(parts[1], g) ||
        !parseUint8(parts[2], b))
    {
        return false;
    }

    color.r = r;
    color.g = g;
    color.b = b;

    return true;
}

static void handleCredentials(ParsedParam parsedParams[MAX_PARAM_COUNT], int paramsCount)
{
    const char *ssid = nullptr;
    const char *password = nullptr;

    for (int i = 0; i < paramsCount; i++)
    {
        if (!strcmp(parsedParams[i].key, "ssid"))
        {
            ssid = parsedParams[i].value;
        }
        else if (strcmp(parsedParams[i].key, "pass"))
        {
            password = parsedParams[i].value;
        }
    }

    if (!ssid && paramsCount >= 1)
    {
        ssid = parsedParams[0].value;
    }
    if (!password && paramsCount >= 2)
    {
        password = parsedParams[1].value;
    }

    if (!isValidLength(ssid, 1, 32) || !isValidLength(password, 0, 63))
    {
        return;
    }

    connectToWiFi(ssid, password);
}

static void handleMode(ParsedParam parsedParams[MAX_PARAM_COUNT], int paramsCount)
{
    CRGB color;

    for (int i = 0; i < paramsCount; i++)
    {
        if (!strcmp(parsedParams[i].key, "name") && parsedParams[i].value[0] != '\0')
            setCurrentMode(parsedParams[i].value);
        else if (!strcmp(parsedParams[i].key, "pri") && parseRGB(parsedParams[i].value, color))
            params.setPrimary(color);
        else if (!strcmp(parsedParams[i].key, "sec") && parseRGB(parsedParams[i].value, color))
            params.setSecondary(color);
        else if (!strcmp(parsedParams[i].key, "spd"))
        {
            uint8_t speed;
            if (parseUint8(parsedParams[i].value, speed))
            {
                float minInterval = modes[currentMode]->getMinFrameInterval();
                float maxInterval = modes[currentMode]->getMaxFrameInterval();
                params.setFrameInterval(speedToInterval(speed, minInterval, maxInterval));
            }
        }
        else if (!strcmp(parsedParams[i].key, "lgt"))
        {
            uint16_t length;
            if (parseUint16(parsedParams[i].value, length))
            {
                uint16_t clampedLength = clamp(length, 1, MAX_LEDS);

                if (currentMode == LED_COUNT_SETUP)
                {
                    params.setLedCount(clampedLength);
                }
                else
                {
                    params.setLength(clampedLength);
                }
            }
        }
        else if (!strcmp(parsedParams[i].key, "bri"))
        {
            uint8_t brightness;
            if (parseUint8(parsedParams[i].value, brightness))
            {
                params.setBrightness(brightness);
            }
        }
    }
    showCurrentMode();
}

static void parseParams(char *key, char *value)
{
    ParsedParam parsedParams[MAX_PARAM_COUNT];
    int count = parseParamPairs(value, parsedParams, MAX_PARAM_COUNT);

    if (count < 0)
    {
        return;
    }

    if (!strcmp(key, "CRD"))
    {
        handleCredentials(parsedParams, count);
    }
    else if (!strcmp(key, "MODE"))
    {
        handleMode(parsedParams, count);
    }
};

void parseMessage(char *message)
{
    Serial.println(message);

    if (!strcmp(message, "CNT"))
    {
        blink(SUCCESS_COLOR, 2);
        showCurrentMode();
    }
    else if (!strcmp(message, "DSCNT"))
    {
        ESP.restart();
    }
    else if (!strcmp(message, "P_OFF"))
    {
        params.setPower(false);
    }
    else if (!strcmp(message, "P_ON"))
    {
        params.setPower(true);
    }
    else
    {
        char *key = message;
        char *value = strchr(message, ' ');
        if (value)
        {
            *value = '\0';
            value++;

            parseParams(key, value);
        }
    }
}
