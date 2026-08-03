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
  while (!Serial) delay(10);

  // Initialize SD card (same as before)
  SPI.setRX(MISO_PIN);
  SPI.setTX(MOSI_PIN);
  SPI.setSCK(SCK_PIN);
  SPI.begin();

  SDFSConfig cfg;
  cfg.setCSPin(CS_PIN);
  cfg.setSPI(SPI);

  if (!SDFS.setConfig(cfg) || !SDFS.begin()) {
    Serial.println("[ERROR] SD initialization failed");
    return;
  }

  Serial.println("[OK] SD card ready");

  // === WRITE OPERATION ===
  Serial.println("\nWriting to file...");
  File myFile = SDFS.open("/test.txt", "w");

  if (!myFile) {
    Serial.println("[ERROR] ERROR: Could not create file");
    return;
  }

  // Write test data
  myFile.println("RP2350 Test Line 1");
  myFile.println("RP2350 Test Line 2");
  myFile.println("Timestamp: " + String(millis()));

  // CRITICAL: Call flush() to ensure data integrity
  myFile.flush();

  myFile.close();
  Serial.println("[OK] File written successfully");

  // === READ OPERATION ===
  Serial.println("\nReading from file...");
  myFile = SDFS.open("/test.txt", "r");

  if (!myFile) {
    Serial.println("[ERROR] ERROR: Could not open file");
    return;
  }

  Serial.println("Content:");
  while (myFile.available()) {
    Serial.write(myFile.read());
  }

  myFile.close();
  Serial.println("\n[OK] File read successfully");
}

void loop() {
  // Nothing to do
}
