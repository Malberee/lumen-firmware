#include "utils.h"

void fillLeds(CRGB color, byte start, byte end)
{
  if (start >= NUM_LEDS)
  {
    return;
  }

  if (end >= NUM_LEDS)
  {
    end = NUM_LEDS - 1;
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
  CRGB lastElement = leds[NUM_LEDS - 1];

  for (size_t i = NUM_LEDS - 1; i > 0; i--)
  {
    leds[i] = leds[i - 1];
  }

  leds[0] = lastElement;
}

static int8_t hexDigitValue(char value)
{
  if (value >= '0' && value <= '9')
  {
    return value - '0';
  }
  if (value >= 'a' && value <= 'f')
  {
    return value - 'a' + 10;
  }
  if (value >= 'A' && value <= 'F')
  {
    return value - 'A' + 10;
  }

  return -1;
}

bool hexToCRGB(const char *hex, CRGB &color)
{
  if (!hex)
  {
    return false;
  }

  if (hex[0] == '#')
  {
    hex++;
  }

  for (byte i = 0; i < 6; i++)
  {
    if (hexDigitValue(hex[i]) < 0)
    {
      return false;
    }
  }

  if (hex[6] != '\0')
  {
    return false;
  }

  color = CRGB(
      (hexDigitValue(hex[0]) << 4) | hexDigitValue(hex[1]),
      (hexDigitValue(hex[2]) << 4) | hexDigitValue(hex[3]),
      (hexDigitValue(hex[4]) << 4) | hexDigitValue(hex[5]));

  return true;
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

bool parseClampedLong(const char *value, long minValue, long maxValue, long &result)
{
  if (!value || value[0] == '\0')
  {
    return false;
  }

  char *end = nullptr;
  long parsed = strtol(value, &end, 10);
  if (end == value || *end != '\0')
  {
    return false;
  }

  if (parsed < minValue)
  {
    parsed = minValue;
  }
  else if (parsed > maxValue)
  {
    parsed = maxValue;
  }

  result = parsed;
  return true;
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
