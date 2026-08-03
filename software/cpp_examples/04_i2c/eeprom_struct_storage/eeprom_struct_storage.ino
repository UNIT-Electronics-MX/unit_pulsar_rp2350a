// Source: PULSAR RP2350 technical wiki, 4-I2C-Communication.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define EEPROM_ADDR 0x50

// Simple data structure to store
struct SensorConfig {
  uint16_t sampleRate;    // Samples per second
  uint8_t  gainLevel;     // 0-15
  uint32_t calibration;   // Calibration value
  char     label[16];     // Name
};

void eepromReadSeq(uint16_t memAddr, uint8_t *buf, size_t len) {
  // [Same as before]
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write(memAddr >> 8);
  Wire.write(memAddr & 0xFF);
  Wire.endTransmission(false);

  size_t received = 0;
  while (received < len) {
    size_t request = (len - received > 32) ? 32 : (len - received);
    Wire.requestFrom(EEPROM_ADDR, (int)request);
    while (Wire.available() && received < len) {
      buf[received++] = Wire.read();
    }
  }
}

void eepromWriteSeq(uint16_t memAddr, const uint8_t *data, size_t len) {
  // [Same as before]
  const size_t pageSize = 32;
  size_t offset = 0;

  while (offset < len) {
    size_t pageSpace = pageSize - ((memAddr + offset) % pageSize);
    size_t chunk = (len - offset < pageSpace) ? (len - offset) : pageSpace;

    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((memAddr + offset) >> 8);
    Wire.write((memAddr + offset) & 0xFF);
    Wire.write(data + offset, chunk);
    Wire.endTransmission();

    delay(5);
    offset += chunk;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  // Create config
  SensorConfig config;
  config.sampleRate = 1000;
  config.gainLevel = 8;
  config.calibration = 0x12345678;
  strcpy(config.label, "Sensor-01");

  Serial.println("Saving sensor config to EEPROM...");

  // Write to EEPROM at address 0x0200
  eepromWriteSeq(0x0200, (uint8_t *)&config, sizeof(config));
  delay(20);

  // Read back
  SensorConfig readConfig;
  eepromReadSeq(0x0200, (uint8_t *)&readConfig, sizeof(readConfig));

  Serial.println("\nRead configuration:");
  Serial.print("Sample Rate: ");
  Serial.println(readConfig.sampleRate);

  Serial.print("Gain Level: ");
  Serial.println(readConfig.gainLevel);

  Serial.print("Calibration: 0x");
  Serial.println(readConfig.calibration, HEX);

  Serial.print("Label: ");
  Serial.println(readConfig.label);

  if (readConfig.sampleRate == config.sampleRate) {
    Serial.println("\n[OK] Configuration saved and restored successfully!");
  } else {
    Serial.println("\n[ERROR] Configuration mismatch!");
  }
}

void loop() {
  // Nothing to do
}
