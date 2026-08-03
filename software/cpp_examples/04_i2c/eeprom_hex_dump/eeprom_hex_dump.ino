// Source: PULSAR RP2350 technical wiki, 4-I2C-Communication.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define EEPROM_ADDR 0x50

void eepromReadSeq(uint16_t memAddr, uint8_t *buf, size_t len) {
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

// Print EEPROM contents as hex dump
void dumpEEPROM(uint16_t startAddr, size_t len) {
  uint8_t buf[16];

  for (size_t i = 0; i < len; i += 16) {
    size_t chunk = (len - i > 16) ? 16 : (len - i);
    eepromReadSeq(startAddr + i, buf, chunk);

    // Print address
    Serial.printf("%04X: ", startAddr + i);

    // Print hex values
    for (size_t j = 0; j < chunk; j++) {
      Serial.printf("%02X ", buf[j]);
    }

    // Print ASCII representation
    Serial.print("  |");
    for (size_t j = 0; j < chunk; j++) {
      if (buf[j] >= 32 && buf[j] < 127) {
        Serial.write(buf[j]);
      } else {
        Serial.write('.');
      }
    }
    Serial.println("|");
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  Serial.println("EEPROM Hex Dump (0x0000 - 0x0100)\n");
  dumpEEPROM(0x0000, 256);
}

void loop() {
  // Nothing to do
}
