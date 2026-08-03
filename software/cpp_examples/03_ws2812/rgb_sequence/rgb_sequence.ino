// Source: PULSAR RP2350 technical wiki, 3-WS2812B-Implementation.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <Adafruit_NeoPixel.h>

#define WS_PIN 1
#define LED_COUNT 3

Adafruit_NeoPixel pixels(LED_COUNT, WS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 255, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 255));
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(255, 255, 0));
  pixels.setPixelColor(1, pixels.Color(0, 255, 255));
  pixels.setPixelColor(2, pixels.Color(255, 0, 255));
  pixels.show();
  delay(500);

  pixels.clear();
  pixels.show();
  delay(500);
}
