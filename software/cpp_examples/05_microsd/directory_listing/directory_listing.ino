// Source: PULSAR RP2350 technical wiki, 5-SPI-MicroSD.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <SPI.h>
#include <SDFS.h>

#define MOSI_PIN 3
#define MISO_PIN 4
#define SCK_PIN  2
#define CS_PIN   7

// Function to recursively list files
void listFiles(const char *dirname, uint8_t levels) {
  File root = SDFS.open(dirname, "r");

  if (!root || !root.isDirectory()) {
    Serial.println("Error: Could not open directory");
    return;
  }

  File file = root.openNextFile();

  while (file) {
    // Print indentation based on directory depth
    for (uint8_t i = 0; i < levels; i++) {
      Serial.print("  ");
    }

    if (file.isDirectory()) {
      Serial.print("[DIR]  ");
      Serial.println(file.name());

      // Recurse into subdirectories
      if (levels < 3) {  // Limit recursion depth
        listFiles(file.name(), levels + 1);
      }
    } else {
      Serial.print("[FILE] ");
      Serial.print(file.name());
      Serial.print(" (");
      Serial.print(file.size());
      Serial.println(" bytes)");
    }

    file = root.openNextFile();
  }

  root.close();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  // Initialize SD card
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

  Serial.println("📁 Directory Listing:\n");
  listFiles("/", 0);
}

void loop() {
  // Nothing to do
}
