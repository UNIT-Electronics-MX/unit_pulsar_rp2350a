// Source: PULSAR RP2350 technical wiki, 6-HDMI-Video.md

#include <udvi_hstx.h>

// Configure HSTX pins
DVHSTXPinout pinConfig = {14, 18, 16, 12};
DVHSTX16 display(pinConfig, DVHSTX_RESOLUTION_320x240);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Initializing HDMI display...");

  // Initialize the display
  if (!display.begin()) {
    Serial.println("[ERROR] ERROR: Display initialization failed");
    Serial.println("   - Check GPIO wiring");
    Serial.println("   - Verify library installation");
    Serial.println("   - Try reconnecting HDMI cable");
    while (1) delay(100);  // Halt
  }

  Serial.println("[OK] Display initialized");

  // Clear screen (black)
  display.fillScreen(0x0000);

  // Draw test pattern
  drawTestPattern();

  Serial.println("[OK] Test pattern displayed");
}

void drawTestPattern() {
  // Draw colored squares
  display.fillRect(0, 0, 80, 80, 0xF800);      // Red
  display.fillRect(80, 0, 80, 80, 0x07E0);     // Green
  display.fillRect(160, 0, 80, 80, 0x001F);    // Blue
  display.fillRect(240, 0, 80, 80, 0x07FF);    // Cyan

  display.fillRect(0, 80, 80, 80, 0xF81F);     // Magenta
  display.fillRect(80, 80, 80, 80, 0xFFE0);    // Yellow
  display.fillRect(160, 80, 80, 80, 0xFFFF);   // White
  display.fillRect(240, 80, 80, 80, 0x0000);   // Black
}

void loop() {
  // Nothing to do
}
