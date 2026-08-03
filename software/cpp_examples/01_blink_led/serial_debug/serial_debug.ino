// Source: PULSAR RP2350 technical wiki, 1-Blinking-LED.md

static const int kUserLedPin = 20;  // D13/BUILTIN1 in the V1.3 schematic
void setup() {
  Serial.begin(115200);
  pinMode(kUserLedPin, OUTPUT);
  Serial.println("Blink test started");
}

void loop() {
  digitalWrite(kUserLedPin, HIGH);
  Serial.println("LED ON");
  delay(500);

  digitalWrite(kUserLedPin, LOW);
  Serial.println("LED OFF");
  delay(500);
}
