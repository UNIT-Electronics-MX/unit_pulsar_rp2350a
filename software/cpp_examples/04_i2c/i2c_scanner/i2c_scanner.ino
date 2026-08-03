// Source: PULSAR RP2350 technical wiki, 4-I2C-Communication.md

#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  // Configure I²C pins
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  Serial.println("Starting I²C scan...\n");

  int deviceCount = 0;

  // Scan addresses 1 to 127
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    byte result = Wire.endTransmission();

    if (result == 0) {
      Serial.print("[OK] Device found at 0x");
      Serial.println(addr, HEX);
      deviceCount++;
    }

    delay(2);  // Brief pause between scans
  }

  Serial.print("\nScan complete. Found ");
  Serial.print(deviceCount);
  Serial.println(" device(s)");
}

void loop() {
  // Nothing to do
}
