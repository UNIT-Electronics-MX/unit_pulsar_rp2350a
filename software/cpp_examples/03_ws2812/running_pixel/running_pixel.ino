// Source: PULSAR RP2350 technical wiki, 3-WS2812B-Implementation.md

#include <Adafruit_NeoPixel.h>

#define WS_PIN 1
#define LED_COUNT 3

Adafruit_NeoPixel pixels(LED_COUNT, WS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(32);
  pixels.clear();
  pixels.show();
}

void loop() {
  for (int pixel = 0; pixel < LED_COUNT; pixel++) {
    pixels.clear();
    pixels.setPixelColor(pixel, pixels.Color(0, 0, 255));
    pixels.show();
    delay(150);
  }
}
