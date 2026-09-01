// Source: PULSAR RP2350 technical wiki, 2-ADC-Basics.md

const int adcPin = 26;      //A3
const int ledPin = 22;  // D13/BUILTIN1 in the V1.3 schematic

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  analogReadResolution(12);
}

void loop() {
  int rawValue = analogRead(adcPin);

  if (rawValue > 2048) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  Serial.println(rawValue);
  delay(100);
}
