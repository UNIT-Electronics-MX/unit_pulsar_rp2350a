// Source: PULSAR RP2350 technical wiki, 1-Blinking-LED.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

static const int kUserLedPin = 20;  // D13/BUILTIN1 in the V1.3 schematic

void setup() {
  pinMode(kUserLedPin, OUTPUT);
}

void loop() {
  digitalWrite(kUserLedPin, HIGH);
  delay(500);
  digitalWrite(kUserLedPin, LOW);
  delay(500);
}
