#include "parsing.h"
#include "wifi.h"
#include "params.h"
#include "blink.h"

WiFiUDP udp;
char packetBuffer[255];

int split(char *str, char *ptrs[], char delimiter)
{
    int count = 0;
    char *offset = str;

    while (true)
    {
        ptrs[count++] = offset;
        offset = strchr(offset, delimiter);
        if (offset)
        {
            *offset = 0;
            offset++;
        }
        else
            break;
    }

    return count;
}

void parseParams(char *key, char *value)
{
    char *ptrs[5];
    char *parsedPtrs[5][2];
    int count = split(value, ptrs, ';');

    for (int i = 0; i < count; i++)
    {
        split(ptrs[i], parsedPtrs[i], '=');
    }

    if (!strcmp(key, "CRD"))
    {
        connectToWiFi(parsedPtrs[0][1], parsedPtrs[1][1]);
    }
    else if (!strcmp(key, "MODE"))
    {
        for (int i = 0; i < count; i++)
        {
            if (!strcmp(parsedPtrs[i][0], "name"))
                setCurrentMode(parsedPtrs[i][1]);
            else if (!strcmp(parsedPtrs[i][0], "pri"))
                params.setPrimary(parsedPtrs[i][1]);
            else if (!strcmp(parsedPtrs[i][0], "sec"))
                params.setSecondary(parsedPtrs[i][1]);
            else if (!strcmp(parsedPtrs[i][0], "spd"))
                params.setSpeed(atoi(parsedPtrs[i][1]));
            else if (!strcmp(parsedPtrs[i][0], "lgt"))
                params.setLength(atoi(parsedPtrs[i][1]));
            else if (!strcmp(parsedPtrs[i][0], "bri"))
                FastLED.setBrightness(atoi(parsedPtrs[i][1]));
        }
        showCurrentMode();
    }
};

void parseUDP()
{
    int packetSize = udp.parsePacket();

    if (packetSize)
    {
        int n = udp.read(packetBuffer, 255);
        packetBuffer[n] = 0;

        Serial.println(packetBuffer);

        if (!strcmp(packetBuffer, "CNT"))
        {
            blink(SUCCESS_COLOR, 2);
            udp.beginPacket(udp.remoteIP(), 8888);
            udp.write("OK");
            udp.endPacket();
        }
        else if (!strcmp(packetBuffer, "DSCNT"))
        {
            ESP.restart();
        }
        else if (!strcmp(packetBuffer, "P_OFF"))
        {
            params.setPower(false);
        }
        else if (!strcmp(packetBuffer, "P_ON"))
        {
            params.setPower(true);
        }
        else
        {
            char *key = packetBuffer;
            char *value = strchr(packetBuffer, ' ');
            if (value)
            {
                *value = 0;
                value++;

                parseParams(key, value);
            }
        }
    }
}
