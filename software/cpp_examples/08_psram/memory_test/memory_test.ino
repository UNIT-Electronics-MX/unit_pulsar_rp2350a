// Source: PULSAR RP2350 technical wiki, 8-PSRAM-Memory.md

#define TEST_SIZE (6 * 1024 * 1024)  // Test 6 MB
uint8_t testData[TEST_SIZE] PSRAM;

void testPSRAM() {
  Serial.println("\n========== PSRAM Test Start ==========");

  // === WRITE TEST ===
  Serial.println("Writing 6MB pattern...");
  unsigned long writeStart = millis();

  for (uint32_t i = 0; i < TEST_SIZE; i += 100000) {
    for (uint32_t j = i; j < i + 100000 && j < TEST_SIZE; j++) {
      testData[j] = (j & 0xFF);
    }
    if (i % 1000000 == 0) Serial.print(".");
  }

  unsigned long writeTime = millis() - writeStart;
  Serial.print("\n[OK] Write completed in ");
  Serial.print(writeTime);
  Serial.println(" ms");

  // === READ & VERIFY TEST ===
  Serial.println("Verifying 6MB pattern...");
  unsigned long readStart = millis();

  uint32_t errorCount = 0;
  for (uint32_t i = 0; i < TEST_SIZE; i += 100000) {
    for (uint32_t j = i; j < i + 100000 && j < TEST_SIZE; j++) {
      if (testData[j] != (j & 0xFF)) {
        errorCount++;
        if (errorCount <= 10) {  // Print first 10 errors
          Serial.print("Error at offset 0x");
          Serial.println(j, HEX);
        }
      }
    }
    if (i % 1000000 == 0) Serial.print(".");
  }

  unsigned long readTime = millis() - readStart;
  Serial.print("\n[OK] Verification completed in ");
  Serial.print(readTime);
  Serial.println(" ms");

  if (errorCount == 0) {
    Serial.println("[OK] All data verified correctly!");
  } else {
    Serial.print("[ERROR] Found ");
    Serial.print(errorCount);
    Serial.println(" errors");
  }

  // === PERFORMANCE STATS ===
  Serial.println("\n--- Performance Stats ---");
  Serial.print("Write bandwidth: ");
  Serial.print((TEST_SIZE / 1024) / (float)writeTime);
  Serial.println(" KB/ms");

  Serial.print("Read bandwidth: ");
  Serial.print((TEST_SIZE / 1024) / (float)readTime);
  Serial.println(" KB/ms");

  Serial.println("========== PSRAM Test End ==========\n");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  #if defined(RP2350_PSRAM_CS)
    if (rp2040.getPSRAMSize() > 0) {
      testPSRAM();
    } else {
      Serial.println("[ERROR] PSRAM not detected");
    }
  #else
    Serial.println("[ERROR] PSRAM not configured");
  #endif
}

void loop() {
  delay(1000);
}
