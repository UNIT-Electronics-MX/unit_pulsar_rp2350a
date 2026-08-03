// Source: PULSAR RP2350 technical wiki, 8-PSRAM-Memory.md

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Dynamic PSRAM allocation test...");

  // Allocate 2 MB from PSRAM
  size_t allocSize = 2 * 1024 * 1024;  // 2 MB

  void *ptr = pmalloc(allocSize);

  if (ptr == NULL) {
    Serial.println("[ERROR] PSRAM allocation failed");
    return;
  }

  Serial.print("[OK] Allocated ");
  Serial.print(allocSize / (1024*1024));
  Serial.println(" MB from PSRAM");

  // Write pattern to allocated memory
  Serial.println("Writing pattern...");
  uint8_t *buffer = (uint8_t *)ptr;
  for (size_t i = 0; i < 1024*100; i++) {
    buffer[i] = i & 0xFF;
  }

  Serial.println("[OK] Pattern written");

  // Verify pattern
  Serial.println("Verifying pattern...");
  bool valid = true;
  for (size_t i = 0; i < 1024*100; i++) {
    if (buffer[i] != (i & 0xFF)) {
      valid = false;
      break;
    }
  }

  if (valid) {
    Serial.println("[OK] Pattern verified");
  } else {
    Serial.println("[ERROR] Pattern verification failed");
  }

  // Free memory
  // The UNIT RP2350 core routes free() to the PSRAM allocator for pmalloc().
  free(ptr);
  Serial.println("[OK] Memory freed");
}

void loop() {
  // Nothing to do
}
