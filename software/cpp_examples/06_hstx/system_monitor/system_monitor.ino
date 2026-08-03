// Source: PULSAR RP2350 technical wiki, 6-HDMI-Video.md

#include <udvi_hstx.h>

DVHSTXPinout pinConfig = {14, 18, 16, 12};
DVHSTX16 display(pinConfig, DVHSTX_RESOLUTION_320x240);

unsigned long lastUpdate = 0;
uint32_t frameCount = 0;

void displaySystemInfo() {
  // Clear info area
  display.fillRect(10, 30, 300, 150, 0x0000);

  // Title
  display.setTextSize(2);
  display.setTextColor(0x07FF);  // Cyan
  display.setCursor(80, 10);
  display.print("System Info");

  // Info text
  display.setTextSize(1);
  display.setTextColor(0xFFFF);  // White

  display.setCursor(20, 40);
  display.print("Uptime: ");
  display.print(millis() / 1000);
  display.print("s");

  display.setCursor(20, 55);
  display.print("Free RAM: ");
  display.print(rp2040.getFreeHeap() / 1024);
  display.print("KB");

  display.setCursor(20, 70);
  display.print("Frame: ");
  display.print(frameCount);

  // Status bar at bottom
  display.fillRect(0, 220, 320, 20, 0x001F);  // Blue bar
  display.setTextColor(0xFFFF);
  display.setCursor(10, 224);
  display.print("RP2350 Monitor");
}

void setup() {
  Serial.begin(115200);

  if (!display.begin()) {
    Serial.println("[ERROR] Display failed");
    while (1) delay(100);
  }

  display.fillScreen(0x0000);
  Serial.println("[OK] System monitor started");
}

void loop() {
  if (millis() - lastUpdate >= 100) {  // 10 FPS
    displaySystemInfo();
    frameCount++;
    lastUpdate = millis();
  }

  delay(50);
}
