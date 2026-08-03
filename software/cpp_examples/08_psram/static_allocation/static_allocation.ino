// Source: PULSAR RP2350 technical wiki, 8-PSRAM-Memory.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

// ========== PSRAM LOCATION ==========
// These variables live in external PSRAM, not internal SRAM

#if defined(RP2350_PSRAM_CS)
  // 1MB buffer for large data
  uint8_t bigBuffer[1024*1024] PSRAM;

  // Array of 10,000 integers (40 KB)
  int dataArray[10000] PSRAM;

  // String buffer (64 KB)
  char textBuffer[64*1024] PSRAM;
#else
  #error "PSRAM not configured. Set Tools > PSRAM CS > GPIO 0"
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Testing PSRAM variables...");

  // Initialize buffer with pattern
  for (int i = 0; i < 1024*10; i++) {
    bigBuffer[i] = (i & 0xFF);
  }

  Serial.println("[OK] Writing to bigBuffer");

  // Initialize array
  for (int i = 0; i < 10000; i++) {
    dataArray[i] = i * 2;
  }

  Serial.println("[OK] Writing to dataArray");

  // Display sizes
  Serial.print("bigBuffer size: ");
  Serial.print(sizeof(bigBuffer) / 1024);
  Serial.println(" KB (in PSRAM)");

  Serial.print("dataArray size: ");
  Serial.print(sizeof(dataArray) / 1024);
  Serial.println(" KB (in PSRAM)");

  Serial.print("RAM saved: ");
  Serial.print((sizeof(bigBuffer) + sizeof(dataArray)) / 1024);
  Serial.println(" KB");
}

void loop() {
  // Demonstrate reading from PSRAM
  static unsigned long lastCheck = 0;

  if (millis() - lastCheck > 5000) {
    // Verify data integrity
    bool valid = true;
    for (int i = 0; i < 10000; i++) {
      if (dataArray[i] != i * 2) {
        valid = false;
        break;
      }
    }

    if (valid) {
      Serial.println("[OK] PSRAM data verified");
    } else {
      Serial.println("[ERROR] PSRAM data corrupted!");
    }

    lastCheck = millis();
  }
}
