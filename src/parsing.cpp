#include "parsing.h"
#include "wifi.h"
#include "params.h"
#include "blink.h"
#include "utils.h"

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
    for (int i = 0; i < paramsCount; i++)
    {
        if (!strcmp(parsedParams[i].key, "name") && parsedParams[i].value[0] != '\0')
            setCurrentMode(parsedParams[i].value);
        else if (!strcmp(parsedParams[i].key, "pri"))
            params.setPrimary(parsedParams[i].value);
        else if (!strcmp(parsedParams[i].key, "sec"))
            params.setSecondary(parsedParams[i].value);
        else if (!strcmp(parsedParams[i].key, "spd"))
        {
            uint16_t speed;
            if (parseUint16(parsedParams[i].value, speed))
            {
                params.setSpeed(speed);
            }
        }
        else if (!strcmp(parsedParams[i].key, "lgt"))
        {
            uint16_t length;
            if (parseUint16(parsedParams[i].value, length))
            {
                params.setLength(clamp(length, 1, NUM_LEDS));
            }
        }
        else if (!strcmp(parsedParams[i].key, "bri"))
        {
            uint16_t brightness;
            if (parseUint16(parsedParams[i].value, brightness))
            {
                FastLED.setBrightness(static_cast<uint8_t>(clamp(brightness, 0, 255)));
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
