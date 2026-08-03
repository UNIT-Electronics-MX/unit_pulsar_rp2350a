// Source: PULSAR RP2350 technical wiki, 4-I2C-Communication.md

#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define EEPROM_ADDR 0x50

// Read multiple consecutive bytes
void eepromReadSeq(uint16_t memAddr, uint8_t *buf, size_t len) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write(memAddr >> 8);
  Wire.write(memAddr & 0xFF);
  Wire.endTransmission(false);

  size_t received = 0;

  while (received < len) {
    // Request max 32 bytes per transmission
    size_t request = (len - received > 32) ? 32 : (len - received);

    Wire.requestFrom(EEPROM_ADDR, (int)request);

    while (Wire.available() && received < len) {
      buf[received++] = Wire.read();
    }
  }
}

// Write multiple consecutive bytes (page-aligned)
void eepromWriteSeq(uint16_t memAddr, const uint8_t *data, size_t len) {
  const size_t pageSize = 32;  // 24C256 page size
  size_t offset = 0;

  while (offset < len) {
    // Calculate space in current page
    size_t pageSpace = pageSize - ((memAddr + offset) % pageSize);
    size_t chunk = (len - offset < pageSpace) ? (len - offset) : pageSpace;

    // Write chunk
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((memAddr + offset) >> 8);
    Wire.write((memAddr + offset) & 0xFF);
    Wire.write(data + offset, chunk);
    Wire.endTransmission();

    delay(5);  // Write cycle time
    offset += chunk;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  Serial.println("EEPROM Sequential Test\n");

  // Test string
  const char *testString = "Hello RP2350!";
  size_t len = strlen(testString) + 1;  // Include null terminator

  // Write
  Serial.println("Writing string to address 0x0100...");
  eepromWriteSeq(0x0100, (const uint8_t *)testString, len);
  delay(20);

  // Read back
  Serial.println("Reading string back...");
  uint8_t readBuf[64];
  eepromReadSeq(0x0100, readBuf, len);

  Serial.print("Read: ");
  Serial.println((char *)readBuf);

  if (strcmp((char *)readBuf, testString) == 0) {
    Serial.println("[OK] Data matches!");
  } else {
    Serial.println("[ERROR] Data mismatch!");
  }
}

void loop() {
  // Nothing to do
}
