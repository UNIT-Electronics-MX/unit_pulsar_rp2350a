// Source: PULSAR RP2350 technical wiki, 5-SPI-MicroSD.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <SPI.h>
#include <SDFS.h>

#define MOSI_PIN 3
#define MISO_PIN 4
#define SCK_PIN  2
#define CS_PIN   7

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);  // Wait for serial monitor

  Serial.println("Initializing SD card...");

  // Configure SPI pins for RP2350
  SPI.setRX(MISO_PIN);
  SPI.setTX(MOSI_PIN);
  SPI.setSCK(SCK_PIN);
  SPI.begin();

  // Configure SDFS
  SDFSConfig cfg;
  cfg.setCSPin(CS_PIN);
  cfg.setSPI(SPI);

  if (!SDFS.setConfig(cfg)) {
    Serial.println("[ERROR] ERROR: Failed to set SDFS config");
    return;
  }

  if (!SDFS.begin()) {
    Serial.println("[ERROR] ERROR: SD card not initialized");
    Serial.println("   - Check FAT32 format");
    Serial.println("   - Verify GPIO wiring");
    return;
  }

  Serial.println("[OK] SD card initialized successfully");

  // Query capacity through the FSInfo API provided by the UNIT RP2350 core.
  FSInfo info;
  if (SDFS.info(info)) {
    Serial.print("Card Size: ");
    Serial.print(info.totalBytes / (1024 * 1024));
    Serial.println(" MB");
    Serial.print("Used Space: ");
    Serial.print(info.usedBytes / (1024 * 1024));
    Serial.println(" MB");
  } else {
    Serial.println("[WARNING] Card capacity information is unavailable");
  }
}

void loop() {
  // Nothing to do in loop for initialization test
}
