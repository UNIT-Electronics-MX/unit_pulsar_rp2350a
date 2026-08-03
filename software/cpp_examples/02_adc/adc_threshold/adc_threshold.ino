// Source: PULSAR RP2350 technical wiki, 2-ADC-Basics.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

const int adcPin = 26;
const int ledPin = 20;  // D13/BUILTIN1 in the V1.3 schematic

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
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
