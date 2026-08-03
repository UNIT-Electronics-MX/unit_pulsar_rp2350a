## **5 Board Operation**

The hardware design is complete and awaiting fabrication. The procedures below
define the intended bring-up sequence and are backed by the technical wiki and
the compilable sketches under `software/cpp_examples/`. Physical results will
be recorded on the first manufactured units.

### **5.1 Getting Started with Arduino IDE** {.section-page}

1. Install Arduino IDE 2.x.
2. Add the UNIT package index to **Additional Boards Manager URLs**:
   `https://raw.githubusercontent.com/UNIT-Electronics/Uelectronics-RP2040-Arduino-Package/main/package_Uelectronics_rp2040_index.json`
3. Install the UNIT Electronics RP2040/RP2350 package.
4. Select **Generic RP2350** or the PULSAR-specific definition when released.
5. Select the RP2350A chip variant, 16 MiB flash, PSRAM CS GPIO0, and 8 MiB
   PSRAM.
6. Connect a USB-C data cable and select the enumerated serial/boot port.
7. Open the basic Blink sketch and upload it.

The repository examples were compile-checked with the UNIT RP2350 core using a
16 MiB flash and 8 MiB PSRAM configuration. Compile success confirms API and
library compatibility, not electrical operation before fabrication.

### **5.2 First Power-up and Inspection**

Use USB-C for initial power. Inspect component orientation, connector seating,
solder bridges, and the microphone port before energizing the board. If
available, use a current-limited source and monitor the 3.3 V rail.

Do not attach a battery, external `VIN`, HSTX adapter, microSD card, or QWIIC
peripheral for the first power check. Confirm the power indicator and absence
of unexpected heating, then establish USB enumeration and upload behavior.

### **5.3 BOOT and Reset Workflow**

For a normal update, the selected framework may reset the board into its upload
mode automatically. If automatic upload is unavailable:

1. Disconnect external driven signals.
2. Hold BOOT.
3. Press and release reset, or connect USB while BOOT is held.
4. Release BOOT after the ROM boot interface appears.
5. Copy or upload the generated firmware using the toolchain instructions.
6. Reset again to run the application from external flash.

SWD provides an alternative when debugging startup code or recovering a board
whose USB application does not enumerate.

### **5.4 Recommended Bring-up Sequence** {.section-page}

| Order | Subsystem | What the step establishes |
|---:|---|---|
| 1 | User LED | Core execution, GPIO20, and upload path |
| 2 | USB serial | Host communication and diagnostic output |
| 3 | ADC | Basic analog input path |
| 4 | RGB chain | GPIO1 timing and three-pixel order |
| 5 | BMI270 I2C | GPIO8/GPIO9 and onboard sensor communication |
| 6 | QWIIC I2C | GPIO24/GPIO25 and external expansion |
| 7 | PSRAM | GPIO0 selection, capacity detection, and allocation |
| 8 | microSD | SPI-compatible subset, card access, and filesystem |
| 9 | PDM | GPIO10/GPIO11 clock and audio capture |
| 10 | HSTX | GPIO12–GPIO19 pairing and display output |
| 11 | Combined application | Memory ownership and subsystem coexistence |

Testing one subsystem at a time makes pin conflicts and library configuration
errors easier to isolate.

### **5.5 C++ Example Collection** {.section-page}

The `software/cpp_examples/` directory contains 28 complete sketches:

| Group | Sketches | Coverage |
|---|---:|---|
| Blink | 2 | basic and serial-debug LED operation |
| ADC | 2 | continuous reading and threshold indication |
| WS2812 | 3 | color sequence, brightness, running pixel |
| I2C | 7 | scan, BMI270, EEPROM byte/block/dump/structure/multiple devices |
| microSD | 4 | initialize, read/write, list, log |
| HSTX | 3 | test pattern, drawing primitives, system monitor |
| Complete application | 1 | BMI270-controlled HSTX cube |
| PSRAM | 5 | detect, static/dynamic allocate, test, monitor |
| PDM | 1 | capture PCM samples through the PDM library |

The examples reconcile known wiki/API differences: user LED GPIO20, SDFS
capacity through `FSInfo`, directory open mode, `flush()` return type, and
release of `pmalloc()` memory through `free()`.

### **5.6 Memory Planning** {.section-page}

Keep stacks, interrupt state, frequently accessed variables, and small DMA
descriptors in internal SRAM. Place large framebuffers, logging queues, and
historical data in PSRAM. Check every allocation and track free internal and
external heap separately.

HSTX RGB565 graphics can consume a large buffer; microSD and USB also require
working memory. Avoid allocating every maximum-size buffer at startup without
a documented memory budget.

### **5.7 Storage Operation** {.section-page}

Configure the microSD SPI subset on GPIO2, GPIO3, GPIO4, and GPIO7 for the
current SDFS examples. Initialize the card, verify filesystem information, open
only the files needed, call `flush()` after important writes, and close handles
before removal or reset.

For data logging, buffer short records in RAM and write them in bounded batches
rather than performing filesystem operations from an interrupt handler.

### **5.8 Video, Sensor, and Audio Coexistence** {.section-page}

HSTX reserves GPIO12–GPIO19 and may generate continuous DMA/interrupt load.
BMI270 uses GPIO8/GPIO9, PDM uses GPIO10/GPIO11, and microSD uses GPIO2–GPIO7,
so the fixed signal sets do not overlap. They still compete for processor time,
DMA channels, SRAM, PSRAM bandwidth, and power.

Use bounded update rates, partial display redraws, buffered audio acquisition,
and nonblocking storage tasks. A combined application should expose health
information over USB serial or RGB status rather than failing silently.

### **5.9 Troubleshooting Guide** {.section-page}

| Symptom | Checks |
|---|---|
| No USB device | Data-capable cable, BOOT/reset sequence, host port, 3.3 V rail |
| Blink does not run | GPIO20 mapping, selected board/FQBN, successful upload |
| PSRAM unavailable | PSRAM CS GPIO0, 8 MiB option, allocation result |
| BMI270 not found | GPIO8/GPIO9 configuration, address selection, library |
| microSD fails | FAT32, GPIO2/3/4/7, SDFS configuration, card seating |
| PDM returns no data | GPIO10 clock, GPIO11 data, PDM buffer/callback setup |
| HSTX display blank | pair order, adapter/cable orientation, supported timing |
| Unstable combined app | internal heap, PSRAM use, blocking loops, pin conflicts |

Record the exact board revision, package/core version, library versions,
compiler output, power source, and reproduction steps for every bring-up issue.
