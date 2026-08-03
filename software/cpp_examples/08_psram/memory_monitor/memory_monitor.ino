// Source: PULSAR RP2350 technical wiki, 8-PSRAM-Memory.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

void printMemoryStatus() {
  Serial.println("\n========== Memory Status ==========");

  // Internal SRAM
  uint32_t totalHeap = rp2040.getTotalHeap();
  uint32_t freeHeap = rp2040.getFreeHeap();
  uint32_t usedHeap = totalHeap - freeHeap;

  Serial.print("Internal SRAM Total: ");
  Serial.print(totalHeap / 1024);
  Serial.println(" KB");

  Serial.print("Internal SRAM Used: ");
  Serial.print(usedHeap / 1024);
  Serial.print(" KB (");
  Serial.print((usedHeap * 100) / totalHeap);
  Serial.println("%)");

  Serial.print("Internal SRAM Free: ");
  Serial.print(freeHeap / 1024);
  Serial.println(" KB");

  #if defined(RP2350_PSRAM_CS)
    // External PSRAM
    uint32_t psramSize = rp2040.getPSRAMSize();
    uint32_t freePsram = rp2040.getFreePSRAMHeap();
    uint32_t usedPsram = psramSize - freePsram;

    Serial.print("\nExternal PSRAM Total: ");
    Serial.print(psramSize / (1024*1024));
    Serial.println(" MB");

    Serial.print("External PSRAM Used: ");
    Serial.print(usedPsram / 1024);
    Serial.print(" KB (");
    Serial.print((usedPsram * 100) / psramSize);
    Serial.println("%)");

    Serial.print("External PSRAM Free: ");
    Serial.print(freePsram / 1024);
    Serial.println(" KB");
  #endif

  Serial.println("====================================\n");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  printMemoryStatus();
}

void loop() {
  // Print every 5 seconds
  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 5000) {
    printMemoryStatus();
    lastPrint = millis();
  }

  delay(1000);
}
