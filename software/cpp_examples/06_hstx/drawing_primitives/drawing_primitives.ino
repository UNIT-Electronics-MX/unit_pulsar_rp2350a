// Source: PULSAR RP2350 technical wiki, 6-HDMI-Video.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <udvi_hstx.h>

DVHSTXPinout pinConfig = {14, 18, 16, 12};
DVHSTX16 display(pinConfig, DVHSTX_RESOLUTION_320x240);

void drawGraphics() {
  // Clear screen
  display.fillScreen(0x0000);  // Black background

  // Draw lines
  display.drawLine(0, 0, 319, 239, 0xFFFF);    // Diagonal white line
  display.drawLine(319, 0, 0, 239, 0xFFFF);    // Other diagonal

  // Draw rectangles (outline)
  display.drawRect(50, 50, 100, 80, 0xF800);   // Red outline
  display.drawRect(180, 50, 100, 80, 0x07E0);  // Green outline

  // Draw filled rectangles
  display.fillRect(50, 150, 100, 30, 0xFFE0);  // Yellow fill
  display.fillRect(180, 150, 100, 30, 0x001F); // Blue fill

  // Draw circles (filled)
  display.fillCircle(80, 80, 20, 0x07FF);      // Cyan circle
  display.fillCircle(240, 80, 20, 0xF81F);     // Magenta circle

  // Draw circle outline
  display.drawCircle(240, 200, 15, 0xFFE0);    // Yellow circle outline
}

void drawText() {
  // Text in different sizes
  display.setTextSize(1);
  display.setTextColor(0xFFFF);  // White
  display.setCursor(10, 10);
  display.print("Size 1");

  display.setTextSize(2);
  display.setTextColor(0xF800);  // Red
  display.setCursor(10, 30);
  display.print("Size 2");

  display.setTextSize(3);
  display.setTextColor(0x07E0);  // Green
  display.setCursor(10, 60);
  display.print("RP2350");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  if (!display.begin()) {
    Serial.println("[ERROR] Display failed");
    while (1) delay(100);
  }

  Serial.println("Drawing graphics...");
}

void loop() {
  // Draw different demonstrations in sequence

  // Show graphics
  drawGraphics();
  delay(3000);

  // Show text
  drawText();
  delay(3000);

  // Show animation
  drawAnimation();
  delay(2000);
}

void drawAnimation() {
  // Simple animated loading bar
  display.fillScreen(0x0000);

  display.setTextSize(2);
  display.setTextColor(0xFFFF);
  display.setCursor(100, 100);
  display.print("Loading");

  for (int x = 50; x < 270; x += 5) {
    display.fillRect(x, 150, 20, 30, 0x07E0);  // Green bar
    delay(50);
  }
}
