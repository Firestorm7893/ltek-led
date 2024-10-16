#include <Arduino.h>
#include <FastLED.h>
// #include <LEDuino.h>

#define NUM_LEDS 144

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN_1 22
#define DATA_PIN_2 21
#define SEGMENT_LEN 9
#define NUM_SEGMENTS 16
#define NUM_PIXELS 40

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812, DATA_PIN_1, GRB>(leds, NUM_LEDS / 2);               // GRB ordering is assumed
  FastLED.addLeds<WS2812, DATA_PIN_2, GRB>(leds, NUM_LEDS / 2, NUM_LEDS / 2); // GRB ordering is assumed

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(10);
  }
  delay(1000);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(10);
  }
  Serial.setTimeout(1000);
  Serial.begin(576000);
}

byte data[NUM_LEDS * 3];

bool justConnected = false;
float timer = 1;

void loop()
{
  while (!Serial)
  {
    if (!justConnected)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB::Red;
      }
      FastLED.show();
      delay(250);

      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    }
    justConnected = true;
  }

  if (justConnected)
  {
    justConnected = false;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
    delay(250);

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    Serial.println("1093484567786");
  }

  if (Serial.available())
  {
    Serial.readBytes(data, NUM_LEDS * 3);
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
    }
    FastLED.show();
    Serial.write('O');
  }
}