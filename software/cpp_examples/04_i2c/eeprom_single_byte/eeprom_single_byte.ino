// Source: PULSAR RP2350 technical wiki, 4-I2C-Communication.md

#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define EEPROM_ADDR 0x50

// Read single byte from EEPROM
uint8_t eepromReadByte(uint16_t memAddr) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write(memAddr >> 8);     // MSB (high byte)
  Wire.write(memAddr & 0xFF);   // LSB (low byte)
  Wire.endTransmission(false);  // Don't release bus

  Wire.requestFrom(EEPROM_ADDR, 1);  // Request 1 byte

  if (Wire.available()) {
    return Wire.read();
  }

  return 0xFF;  // Return 0xFF if read fails
}

// Write single byte to EEPROM
void eepromWriteByte(uint16_t memAddr, uint8_t data) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write(memAddr >> 8);     // Address MSB
  Wire.write(memAddr & 0xFF);   // Address LSB
  Wire.write(data);              // Data byte
  Wire.endTransmission();        // Release bus

  delay(5);  // EEPROM write cycle time
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  Serial.println("EEPROM Single Byte Test\n");

  // Write byte to address 0x0000
  Serial.println("Writing 0xAB to address 0x0000...");
  eepromWriteByte(0x0000, 0xAB);
  delay(10);

  // Read it back
  Serial.println("Reading from address 0x0000...");
  uint8_t value = eepromReadByte(0x0000);

  Serial.print("Read value: 0x");
  Serial.println(value, HEX);

  if (value == 0xAB) {
    Serial.println("[OK] Write/read successful!");
  } else {
    Serial.println("[ERROR] Mismatch!");
  }
}

void loop() {
  // Nothing to do
}
