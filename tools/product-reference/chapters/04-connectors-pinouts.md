## **4 Connectors & Pinouts**

Pin labels describe hardware revision V1.3. GPIO numbers identify RP2350A signals;
framework aliases depend on the selected board definition.

### **4.1 General Pinout** {.section-page}

| Board label | RP2350A | Primary board role | Shared resource |
|---|---:|---|---|
| `TX0` / `D1` | GPIO18 | UART-capable digital I/O | HSTX Data0 pair |
| `RX0` / `D0` | GPIO19 | UART-capable digital I/O | HSTX Data0 pair |
| `D2` | GPIO17 | Digital I/O | HSTX Data1 pair |
| `D3` | GPIO16 | Digital I/O | HSTX Data1 pair |
| `D4` | GPIO15 | Digital I/O | HSTX clock pair |
| `D5` | GPIO14 | Digital I/O | HSTX clock pair |
| `D6` | GPIO13 | Digital I/O | HSTX Data2 pair |
| `D7` | GPIO12 | Digital I/O | HSTX Data2 pair |
| `D8`, `D9` | Not specified | Board labels present | No RP2350A connection shown in available schematic |
| `D10` / `SS` | GPIO21 | Digital I/O | General-purpose |
| `D11` / `MOSI` | GPIO22 | Digital I/O | General-purpose |
| `D12` / `MISO` | GPIO23 | Digital I/O | General-purpose |
| `D13` / `SCK` / LED | GPIO20 | Digital I/O and user LED | `BUILTIN1` |
| `A1` / `D15` | GPIO29 / ADC3 | Analog-capable I/O | Also routed to HSTX connector |
| `A2` / `D16` | GPIO27 / ADC1 | Analog-capable I/O | Edge pad |
| `A3` / `D17` | GPIO26 / ADC0 | Analog-capable I/O | Edge pad |
| `SDA` / `D18` | GPIO8 | I2C data | BMI270 bus |
| `SCL` / `D19` | GPIO9 | I2C clock | BMI270 bus |
| `D21` | GPIO10 | PDM clock | ICS-41350 clock |
| `RGB` | GPIO1 | RGB-chain output | Three onboard WS2812 LEDs |

Power and control positions include `3V3`, `3EN`, `VBAT`, `VUSB`, `VIN`,
`RST`, and multiple `GND` pads. Their physical presence does not establish
unreleased input or load limits.

### **4.2 Arduino NANO Pinout Compatibility** {.section-page}

The board uses two parallel 15-position edge rows inspired by the Arduino Nano
layout. This provides a familiar mechanical and labeling pattern, but it is not
a statement of full electrical or shield compatibility.

Important differences include:

- RP2350A uses a 3.3 V logic domain.
- Several conventional positions have PULSAR-specific functions such as
  `VBAT`, `3EN`, `RGB`, and microphone clock.
- GPIO12–GPIO19 are shared with the HSTX video route.
- `D8` and `D9` are not connected to RP2350A in the available schematic.
- Analog channel labels do not form a simple sequential GPIO order.
- The board includes bottom-side connectors and components that may conflict
  mechanically with some carriers.

Before installing the board into a Nano-style carrier, compare every power,
reset, analog, and digital position and verify bottom-side clearance.

### **4.3 QWIIC Connector** {.section-page}

J1 is a four-position, 1 mm-pitch right-angle connector carrying:

| Signal | RP2350A connection | Function |
|---|---:|---|
| GND | Ground | Common return |
| 3.3 V | Regulated rail | Peripheral supply; available current not specified |
| SDA | GPIO24 | External I2C data |
| SCL | GPIO25 | External I2C clock |

The QWIIC bus is separate from the GPIO8/GPIO9 bus used by BMI270. A controlled
contact-number and mating-cable drawing is not included, so verify the physical
orientation against controlled connector data when producing a harness.

### **4.4 MicroSD Connector** {.section-page}

| Socket signal | GPIO | Description |
|---|---:|---|
| `CLK` | 2 | SDIO clock / SPI SCK |
| `CMD` | 3 | SDIO command / SPI MOSI |
| `DAT0` | 4 | SDIO data 0 / SPI MISO |
| `DAT1` | 5 | SDIO data 1 |
| `DAT2` | 6 | SDIO data 2 |
| `DAT3` | 7 | SDIO data 3 / SPI chip select |
| Detect | Dedicated socket contact | Card-detect handling depends on firmware routing |
| VDD | 3.3 V | Card supply |
| GND / shields | Ground | Return and mechanical shield |

Insert and remove a card only when filesystem activity has stopped. Software
must flush and close files before power removal.

### **4.5 Battery Connections**

JP1 is a two-position PH2.0 battery connector associated with `VBAT` and the
battery return. Polarity markings are present on the bottom side. The
MCP73831 charge controller is designed for a single-cell Li-Ion/Li-Polymer
system, but the compatible cell, connector, polarity convention, charge
current, and operating range are not specified by the available module-level
documentation.

Do not connect a battery based solely on connector fit. Reversed polarity or an
unsupported chemistry can damage the board or cell.

### **4.6 HSTX 22-pin Connector** {.section-page}

J5 is a 22-position, 0.5 mm-pitch FFC/FPC connector. The schematic exposes
D0–D7 (GPIO12–GPIO19), A0/GPIO28, A1/GPIO29, GPIO24/SDA,
GPIO25/SCL, 3.3 V, and interleaved returns. HSTX video uses the eight
GPIO12–GPIO19 signals as four TMDS pairs.

The flex-cable contact side, complete numbered contact table, cable length, and
display adapter are not specified by a controlled mechanical drawing. Do not infer pin
1 from an unannotated photograph.

### **4.7 USB-C, BOOT, and Reset**

The USB-C connector carries VBUS and the RP2350A USB data pair. The schematic
shows the required USB-C configuration resistors and ESD protection. USB is the
preferred programming and first-power interface.

BOOT selects the ROM USB boot path used for firmware recovery or initial
programming. Reset restarts RP2350A while power remains applied. Exact button
timing depends on the selected toolchain, but the common sequence is to hold
BOOT while resetting or connecting USB, then release BOOT after enumeration.

### **4.8 SWD and Test Pads** {.section-page}

Bottom-side pads expose `SWDIO`, `SWCLK`, 3.3 V reference, and GND for an
external debug probe. SWD supports firmware loading and source-level debug when
the toolchain and processor architecture are configured consistently.

Use short connections, share ground, and let the probe sense the target's 3.3 V
rail. Do not use the reference pad to power the complete board unless the debug
probe is explicitly rated and the board power path permits it.
