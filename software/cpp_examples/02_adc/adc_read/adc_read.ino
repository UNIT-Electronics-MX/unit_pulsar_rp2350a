// Source: PULSAR RP2350 technical wiki, 2-ADC-Basics.md

const int adcPin = 26;      //A3

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int rawValue = analogRead(adcPin);
  float voltage = (rawValue / 4095.0f) * 3.3f;

  Serial.print("ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  delay(250);
}
