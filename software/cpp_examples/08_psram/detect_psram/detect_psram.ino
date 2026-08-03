// Source: PULSAR RP2350 technical wiki, 8-PSRAM-Memory.md
// Hardware design status: complete, awaiting fabrication.
// Confirm runtime results on the first manufactured units.

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Checking PSRAM...");

  // Check if PSRAM is configured
  #if defined(RP2350_PSRAM_CS)
    Serial.print("[OK] PSRAM CS configured on GPIO ");
    Serial.println(RP2350_PSRAM_CS);
  #else
    Serial.println("[ERROR] ERROR: PSRAM CS not defined!");
    Serial.println("   Fix: Tools > PSRAM CS > GPIO 0");
    while(1);  // Halt
  #endif

  // Get PSRAM size
  uint32_t psramSize = rp2040.getPSRAMSize();

  if (psramSize == 0) {
    Serial.println("[ERROR] ERROR: No PSRAM detected");
    Serial.println("   - Check chip wiring");
    Serial.println("   - Verify chip is powered");
    while(1);
  }

  Serial.print("[OK] PSRAM detected: ");
  Serial.print(psramSize / (1024*1024));
  Serial.println(" MB");

  // Get free PSRAM
  uint32_t freePsram = rp2040.getFreePSRAMHeap();
  Serial.print("[OK] Free PSRAM: ");
  Serial.print(freePsram / 1024);
  Serial.println(" KB");
}

void loop() {
  // Nothing to do
}
