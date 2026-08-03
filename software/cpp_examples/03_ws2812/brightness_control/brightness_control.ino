// Source: PULSAR RP2350 technical wiki, 3-WS2812B-Implementation.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <Adafruit_NeoPixel.h>

#define WS_PIN 1
#define LED_COUNT 3

Adafruit_NeoPixel pixels(LED_COUNT, WS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(32);
}

void loop() {
  for (int i = 0; i < 255; i += 5) {
    for (int pixel = 0; pixel < LED_COUNT; pixel++) {
      pixels.setPixelColor(pixel, pixels.Color(i, 0, 255 - i));
    }
    pixels.show();
    delay(20);
  }
}
