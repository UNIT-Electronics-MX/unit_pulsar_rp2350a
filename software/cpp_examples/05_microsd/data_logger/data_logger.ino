// Source: PULSAR RP2350 technical wiki, 5-SPI-MicroSD.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <SPI.h>
#include <SDFS.h>

#define MOSI_PIN 3
#define MISO_PIN 4
#define SCK_PIN  2
#define CS_PIN   7

unsigned long lastLogTime = 0;
const unsigned long LOG_INTERVAL = 5000;  // Log every 5 seconds
uint32_t logCounter = 0;

void logData() {
  // Open file in append mode
  File logFile = SDFS.open("/data_log.csv", "a");

  if (!logFile) {
    Serial.println("[ERROR] Could not open log file");
    return;
  }

  // Write timestamp and counter
  logFile.print(millis());
  logFile.print(",");
  logFile.print(logCounter++);
  logFile.print(",");
  logFile.println(analogRead(A0));  // Example: read analog value

  logFile.flush();
  logFile.close();

  Serial.print("[OK] Data logged (");
  Serial.print(logCounter);
  Serial.println(" entries)");
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

  // Optional: Clear previous log
  // SDFS.remove("/data_log.csv");

  Serial.println("Data logging enabled");
  Serial.println("Logging every " + String(LOG_INTERVAL) + "ms");
}

void loop() {
  if (millis() - lastLogTime >= LOG_INTERVAL) {
    logData();
    lastLogTime = millis();
  }

  delay(100);
}
