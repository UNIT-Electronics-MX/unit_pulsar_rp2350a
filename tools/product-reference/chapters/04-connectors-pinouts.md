## **4 Connectors & Pinouts**

Pin labels describe hardware revision V1.3.0. GPIO numbers identify RP2350A signals; framework aliases depend on the selected board definition.

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
| `D7` | GPIO12 | Digital I/O | HSTX Data2 pair / optional BMI270 INT1 |
| `D8` | USB_DM (pin 51) | USB D- | Shared with USB-C through 22 Ω series resistor R10 |
| `D9` | USB_DP (pin 52) | USB D+ | Shared with USB-C through 22 Ω series resistor R11 |
| `D10` / `SS` | GPIO21 | Digital I/O | General-purpose |
| `D11` / `MOSI` | GPIO23 | Digital I/O | General-purpose |
| `D12` / `MISO` | GPIO20 | Digital I/O | General-purpose |
| `D13` / `SCK` / LED | GPIO22 | Digital I/O and user LED | `BUILTIN1` |
| `A1` / `D15` | GPIO29 / ADC3 | Analog-capable I/O | Also routed to HSTX connector |
| `A2` / `D16` | GPIO27 / ADC1 | Analog-capable I/O | Castellated header |
| `A3` / `D17` | GPIO26 / ADC0 | Analog-capable I/O | Castellated header |
| `SDA` / `D18` | GPIO8 | I2C data | BMI270 bus |
| `SCL` / `D19` | GPIO9 | I2C clock | BMI270 bus |
| `D21` / `CLK_MIC` | GPIO10 | PDM clock | ICS-41350 clock |
| `DATA_MIC` | GPIO11 | PDM data input | ICS-41350 data |
| `RGB` | GPIO1 | NeoPixel data input | Three onboard WS2812 LEDs |
| `NEOPIXEL DOUT` | — | RGB-chain extension output | Available at castellated header when `RGB_PAD` is closed |

Power and control positions include `3V3`, `3EN`, `VBAT`, `5V`, `VIN`, `RESET`, and multiple `GND` connections.

`3EN`, `VBAT`, and `NEOPIXEL DOUT` are disconnected from their castellated-header positions by default to preserve the Nano-style pin layout. They can be enabled individually by closing the corresponding solder pads on the bottom side of the PCB.

The `3EN` position provides access to the AP2112K `EN` signal when its corresponding solder jumper is closed, allowing external control of the 3.3 V regulator.

The `INT_PAD` solder jumper optionally connects BMI270 `INT1` to `D7` / GPIO12.

### **4.2 Arduino Nano Pinout Compatibility** {.section-page}

The board uses two parallel 15-position castellated edge rows inspired by the Arduino Nano layout. This provides a familiar mechanical footprint and labeling pattern, but does not imply full electrical or shield compatibility.

Important differences include:

- The RP2350A and board GPIO operate in the 3.3 V logic domain.
- Several conventional positions have PULSAR-specific functions, including `VBAT`, `3EN`, `NEOPIXEL DOUT`, and PDM microphone signals.
- `3EN`, `VBAT`, and `NEOPIXEL DOUT` are disconnected from their castellated-header positions by default and can be enabled through bottom-side solder jumpers.
- `D7` / GPIO12 can optionally receive the BMI270 `INT1` signal by closing `INT_PAD`.
- GPIO12–GPIO19 are shared with the HSTX video interface.
- `D8` and `D9` carry the RP2350A native USB D-/D+ signals. They are connected to the same differential pair used by the USB-C connector through 22 Ω series resistors and should not be treated as conventional digital I/O.
- Analog channel labels do not follow a simple sequential GPIO order.
- Bottom-side connectors and components may require additional clearance when the board is installed in a carrier.

Before installing the board into a Nano-style carrier, verify power, reset, analog, digital, and mechanically shared positions, as well as bottom-side clearance.

### **4.3 QWIIC Connector** {.section-page}

J1 is a four-position, 1 mm-pitch QWIIC connector carrying:

| Signal | RP2350A connection | Function |
|---|---:|---|
| GND | Ground | Common return |
| 3.3 V | Regulated rail | Peripheral supply |
| SDA | GPIO24 | External I2C data |
| SCL | GPIO25 | External I2C clock |

The QWIIC interface operates in the 3.3 V logic domain and is separate from the GPIO8/GPIO9 I2C bus used by the onboard BMI270.

The QWIIC 3.3 V supply is provided by the same AP2112K regulator used by the board. The regulator supports up to 600 mA total output current, shared between the onboard circuitry and all external 3.3 V loads.

Use 3.3 V-compatible QWIIC peripherals and verify connector orientation before connection.

### **4.4 MicroSD Connector** {.section-page}

| Socket signal | GPIO | Description |
|---|---:|---|
| `CLK` | GPIO2 | SDIO clock / SPI SCK |
| `CMD` | GPIO3 | SDIO command / SPI MOSI |
| `DAT0` | GPIO4 | SDIO data 0 / SPI MISO |
| `DAT1` | GPIO5 | SDIO data 1 |
| `DAT2` | GPIO6 | SDIO data 2 |
| `DAT3` | GPIO7 | SDIO data 3 / SPI chip select |
| VDD | 3.3 V | Card supply |
| GND / shield | Ground | Electrical return and connector shield |

The microSD interface supports the complete four-bit SDIO signal group. Current UNIT Electronics Wiki examples use the SPI-compatible subset.

Insert or remove the microSD card only when filesystem activity has stopped. Software should flush and close open files before card extraction or power removal.

### **4.5 Battery Connections** {.section-page}

JP1 provides the battery connection for a single-cell LiPo battery. Hardware V1.3.0 supports PH2.0 mm or PH1.25 mm battery connector options depending on the assembled configuration.

The battery input is designed for a single-cell LiPo battery with a nominal voltage of 3.7 V and a maximum fully charged voltage of 4.2 V. Battery charging is managed by the onboard MCP73831T-2ACI/OT and is configured for a nominal charge current of 200 mA.

Polarity markings are provided on the bottom side of the PCB. Always verify connector polarity before connecting a battery, as connector compatibility alone does not guarantee correct polarity.

The `VBAT_PAD` solder jumper can connect the battery rail to the corresponding castellated-header position. This connection is open by default. When the solder jumper is closed, the battery voltage becomes available at the `VBAT` castellated pad.

Do not connect multi-cell battery packs or batteries exceeding 4.2 V.

### **4.6 HSTX 22-pin Connector** {.section-page}

J5 is a 22-position, 0.5 mm-pitch FFC/FPC connector that provides the RP2350A HSTX interface together with auxiliary I2C, analog, power, and ground connections.

| Pin | Signal | RP2350A connection | Function |
|---:|---|---|---|
| 1 | `D7` / `INT1` | GPIO12 | HSTX Data2 / optional BMI270 INT1 |
| 2 | GND | Ground | HSTX return |
| 3 | `D6` | GPIO13 | HSTX Data2 |
| 4 | `D5` | GPIO14 | HSTX clock |
| 5 | GND | Ground | HSTX return |
| 6 | `D4` | GPIO15 | HSTX clock |
| 7 | `D3` | GPIO16 | HSTX Data1 |
| 8 | GND | Ground | HSTX return |
| 9 | `D2` | GPIO17 | HSTX Data1 |
| 10 | `D1` | GPIO18 | HSTX Data0 |
| 11 | GND | Ground | HSTX return |
| 12 | `D0` | GPIO19 | HSTX Data0 |
| 13 | `A1` / `D15` | GPIO29 / ADC3 | Analog-capable auxiliary signal |
| 14 | GND | Ground | Return |
| 15 | `A0` | GPIO28 / ADC2 | Analog-capable auxiliary signal |
| 16 | GND | Ground | Return |
| 17 | `SDA` | GPIO24 | External I2C data |
| 18 | GND | Ground | I2C / auxiliary return |
| 19 | `SCL` | GPIO25 | External I2C clock |
| 20 | GND | Ground | I2C / auxiliary return |
| 21 | 3.3 V | Regulated 3.3 V rail | Peripheral supply |
| 22 | GND | Ground | Power return |

GPIO12 through GPIO19 provide the eight high-speed signals used by the RP2350A HSTX interface. In the DVI-compatible configuration, these signals form the four differential signal pairs required for video output.

The connector also exposes GPIO24 and GPIO25 for the external I2C bus, GPIO28 and GPIO29 as analog-capable auxiliary signals, and the regulated 3.3 V rail.

The UNIT DevLab DVI to FPC Adapter can be used with this connector to provide a DVI-compatible video interface.

When HSTX video output is active, GPIO12–GPIO19 must not be simultaneously driven by external circuitry through the castellated headers or other connections.

The `INT_PAD` solder jumper can connect BMI270 `INT1` to GPIO12 (`D7`). Because GPIO12 is also part of the HSTX interface, applications using HSTX must account for this shared connection before closing `INT_PAD`.

Use a compatible 22-position, 0.5 mm-pitch FFC/FPC cable and verify cable contact orientation before connection. Remove board power before inserting or removing the FFC/FPC cable.

### **4.7 USB-C, BOOT, and Reset** {.section-page}

J2 provides USB-C power, programming, and USB data connectivity. The USB D- and D+ signals connect to the RP2350A native USB PHY and are also exposed at the `D8` and `D9` positions through 22 Ω series resistors.

The BOOT button selects the RP2350A ROM USB boot mode used for firmware programming and recovery. The RESET button restarts the RP2350A while board power remains applied.

A typical firmware-recovery sequence is to hold BOOT while resetting or connecting USB, then release BOOT after the device enters USB boot mode.

### **4.8 SWD and Debug Pads** {.section-page}

Bottom-side debug pads expose `SWDIO`, `SWCLK`, 3.3 V reference, and GND for connection to an external SWD debug probe. The SWD interface supports firmware programming and source-level debugging of the RP2350A.

**Silkscreen erratum:** The SWD `VCC` and `GND` labels are reversed. Refer to Section 9.6 for the corrected mapping before connecting a debug probe.

Use short debug connections and ensure that the target board and debug probe share a common ground. The 3.3 V pad should be used as the target-voltage reference for the debug probe and should not be used to power the complete board unless the probe and board power configuration explicitly support it.
