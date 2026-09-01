// Source: PULSAR RP2350 technical wiki, 1-Blinking-LED.md

static const int kUserLedPin = 22;  // D13/BUILTIN1 in the V1.3 schematic

void setup() {
  pinMode(kUserLedPin, OUTPUT);
}

void loop() {
  digitalWrite(kUserLedPin, HIGH);
  delay(500);
  digitalWrite(kUserLedPin, LOW);
  delay(500);
}
