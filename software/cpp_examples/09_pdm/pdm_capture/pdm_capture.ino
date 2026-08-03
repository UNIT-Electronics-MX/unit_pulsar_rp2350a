// Source: PULSAR RP2350 technical wiki, 9-PDM-Microphone.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

#include <Arduino.h>
#include <PDM.h>

static const int kSampleRate = 8000;
static const int kChannels = 1;
static const size_t kSampleBufferCount = 256;

// Board internal PDM pins
static const int kPdmDinPin = 11;
static const int kPdmClkPin = 10;

static int16_t sampleBuffer[kSampleBufferCount];
static volatile size_t samplesRead = 0;

void onPdmData() {
  int bytesAvailable = PDM.available();
  if (bytesAvailable <= 0) {
    return;
  }

  int bytesToRead = min(bytesAvailable, (int)sizeof(sampleBuffer));
  int bytesRead = PDM.read((void *)sampleBuffer, bytesToRead);
  if (bytesRead > 0) {
    samplesRead = (size_t)bytesRead / sizeof(sampleBuffer[0]);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  PDM.setDIN(kPdmDinPin);
  PDM.setCLK(kPdmClkPin);
  PDM.onReceive(onPdmData);
  PDM.setBufferSize(sizeof(sampleBuffer));

  if (!PDM.begin(kChannels, kSampleRate)) {
    Serial.println("PDM initialization failed");
    Serial.println("Expected pins: DIN=GPIO11 CLK=GPIO10");
    while (true) {
      delay(100);
    }
  }

  Serial.println("PDM microphone started");
}

void loop() {
  if (samplesRead == 0) {
    delay(1);
    return;
  }

  noInterrupts();
  size_t localCount = samplesRead;
  samplesRead = 0;
  interrupts();

  if (localCount > kSampleBufferCount) {
    localCount = kSampleBufferCount;
  }

  for (size_t i = 0; i < localCount; ++i) {
    Serial.println(sampleBuffer[i]);
  }
}
