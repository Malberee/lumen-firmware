#include "parsing.h"
#include "wifi.h"

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
};

void parseUDP()
{
    int packetSize = udp.parsePacket();

    if (packetSize)
    {
        Serial.println(packetSize);
        int n = udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        packetBuffer[n] = 0;
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
