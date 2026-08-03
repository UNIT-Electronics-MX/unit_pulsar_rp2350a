// Source: PULSAR RP2350 technical wiki, 4-I2C-Communication.md

#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9

#define EEPROM_ADDR   0x50  // EEPROM
#define RTC_ADDR      0x68  // Real-time clock (example)
#define SENSOR_ADDR   0x38  // Sensor (example)

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  Serial.println("Checking I²C devices:\n");

  // Check EEPROM
  Wire.beginTransmission(EEPROM_ADDR);
  if (Wire.endTransmission() == 0) {
    Serial.println("[OK] EEPROM (0x50) - Found");
  } else {
    Serial.println("[ERROR] EEPROM (0x50) - Not found");
  }

  // Check RTC
  Wire.beginTransmission(RTC_ADDR);
  if (Wire.endTransmission() == 0) {
    Serial.println("[OK] RTC (0x68) - Found");
  } else {
    Serial.println("[ERROR] RTC (0x68) - Not found");
  }

  // Check Sensor
  Wire.beginTransmission(SENSOR_ADDR);
  if (Wire.endTransmission() == 0) {
    Serial.println("[OK] Sensor (0x38) - Found");
  } else {
    Serial.println("[ERROR] Sensor (0x38) - Not found");
  }
}

void loop() {
  // Nothing to do
}
