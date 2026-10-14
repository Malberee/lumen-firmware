#include "utils.h"
#include "config.h"
#include "params.h"

void fillLeds(CRGB color, uint16_t start, uint16_t end)
{
  uint16_t ledCount = params.getLedCount();

  if (start >= ledCount)
  {
    return;
  }

  if (end >= ledCount)
  {
    end = ledCount - 1;
  }

  if (end < start)
  {
    return;
  }

  for (int i = start; i <= end; i++)
  {
    leds[i] = color;
  }
}

void rotateLeds()
{
  uint16_t ledCount = params.getLedCount();
  CRGB lastElement = leds[ledCount - 1];

  for (size_t i = ledCount - 1; i > 0; i--)
  {
    leds[i] = leds[i - 1];
  }

  leds[0] = lastElement;
}

int8_t findIndex(const char *arr[], size_t size, const char *target)
{
  if (!target)
  {
    return -1;
  }

  for (size_t i = 0; i < size; ++i)
  {
    if (strcmp(arr[i], target) == 0)
    {
      return static_cast<int8_t>(i);
    }
  }
  return -1;
}

int splitString(char *str, char *ptrs[], byte capacity, char delimiter)
{
  if (!str || !ptrs || capacity == 0)
  {
    return -1;
  }

  int count = 0;
  char *offset = str;

  while (true)
  {
    if (count >= capacity)
    {
      return -1;
    }

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

bool parseUint16(const char *str, uint16_t &value)
{
  if (!str || *str == '\0')
  {
    return false;
  }

  uint16_t result = 0;

  while (*str)
  {
    char c = *str++;

    if (c < '0' || c > '9')
    {
      return false;
    }

    uint8_t digit = c - '0';

    if (result > (UINT16_MAX - digit) / 10)
    {
      return false;
    }

    result = result * 10 + digit;
  }

  value = result;
  return true;
}

bool parseUint8(const char *str, uint8_t &value)
{
  uint16_t parsed;

  if (!parseUint16(str, parsed) || parsed > UINT8_MAX)
  {
    return false;
  }

  value = static_cast<uint8_t>(parsed);
  return true;
}

uint16_t clamp(uint16_t value, uint16_t min, uint16_t max)
{
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

bool isValidLength(const char *value, byte minLength, byte maxLength)
{
  if (!value)
  {
    return false;
  }

  byte length = 0;
  while (value[length] != '\0')
  {
    length++;
    if (length > maxLength)
    {
      return false;
    }
  }

  return length >= minLength;
}

float speedToInterval(uint8_t speed, float minInterval, float maxInterval)
{

  float t = speed / 100.0f;

  return maxInterval *
         pow(minInterval / maxInterval, t);
}

void showLeds()
{
  // FastLED.setBrightness(params.getBrightness());
  controller->show(leds, params.getLedCount(), params.getBrightness());
}