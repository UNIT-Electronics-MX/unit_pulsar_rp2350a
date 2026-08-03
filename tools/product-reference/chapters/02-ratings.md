## **2 Ratings**

This chapter separates values established by the design files from limits that
require measurement or a released board-level specification. A component's
absolute maximum or operating range is not automatically the rating of the
complete PULSAR board.

### **2.1 Recommended Operating Conditions** {.section-page}

Use USB-C as the documented power and programming path. Board-level limits not
defined by the available technical documentation are marked as not specified.

| Parameter | Design-defined value | Board-level status |
|---|---:|---|
| Regulated logic rail | 3.3 V nominal | Defined by AP2112K-3.3; load capability not specified |
| USB VBUS net | +5 V nominal | Shown by schematic net label; USB source quality is external |
| RP2350 system clock | Up to 150 MHz | RP2350 component capability; board default depends on firmware |
| Board reference oscillator | 12 MHz | XTAL1 oscillator frequency |
| Internal SRAM | 520 kB | RP2350 component resource |
| External flash | 128 Mbit / 16 MiB | W25Q128JVPIQ onboard memory |
| External PSRAM | 8 MiB | APS6404L-3SQR-ZR onboard memory |
| `VIN` input | Not specified | No board-level input range supplied |
| Battery input | Not specified | Cell chemistry, range, and cable compatibility not specified |
| Ambient temperature | Not specified | No board-level environmental range supplied |

### **2.2 Power-Domain Scope**

The schematic uses `+5V`, `VBUS`, `VIN`, `VBAT`, `VSYS`, and `3.3V` net names.
These labels describe circuit connectivity, not interchangeable power inputs.
The AP2112K creates the 3.3 V logic rail from `VSYS`; the MCP73831 manages the
battery charging path. Diodes and MOSFETs participate in source routing.

The following values must remain separate:

- **RP2350A ratings:** apply only at RP2350A pins under the conditions in the
  Raspberry Pi datasheet.
- **Regulator ratings:** describe U1 and do not state how much current remains
  available after onboard loads.
- **Charger ratings:** describe IC2; actual charge current depends on the board
  programming network.
- **Connector ratings:** describe the connector hardware, not the permitted
  board supply voltage.
- **Board ratings:** apply to the complete board rather than an individual
  component.

### **2.3 Digital Interfaces**

All onboard digital peripherals are connected to the board's 3.3 V logic
domain. External logic compatibility must nevertheless be checked against the
RP2350A input/output specifications and the power state of both devices.

| Interface | Board connection | Electrical note |
|---|---|---|
| Internal I2C | GPIO8 / GPIO9 | BMI270 bus with onboard pull-ups |
| QWIIC I2C | GPIO24 / GPIO25 | Connector also supplies 3.3 V and GND |
| microSD | GPIO2–GPIO7 | Full SDIO group; wiki uses SPI-compatible subset |
| PDM | GPIO10 / GPIO11 | Clock output and microphone data input |
| HSTX | GPIO12–GPIO19 | High-speed driven pairs; reserve while video is active |
| WS2812 data | GPIO1 | Drives three cascaded onboard LEDs |
| SWD | SWDIO / SWCLK | Use a 3.3 V target reference |

### **2.4 Confirmed Component Values**

| Symbol / parameter | Value | Scope |
|---|---:|---|
| RP2350 internal SRAM | 520 kB | RP2350A component |
| RP2350 system clock | 150 MHz maximum nominal | RP2350A component |
| QSPI flash capacity | 128 Mbit | IC1 |
| PSRAM capacity | 8 MiB | IC4 |
| PDM microphone supply | 1.65 to 3.63 V | ICS-41350 component only |
| LDO output | 3.3 V nominal | U1 component selection |
| Oscillator frequency | 12 MHz | XTAL1 |

### **2.5 Unspecified Board Characteristics** {.section-page}

- `VIN`, `VBAT`, and USB operating and absolute-maximum ranges
- Available 3.3 V current for external loads
- Battery charge current and supported cell/cable compatibility
- Source priority and reverse-current behavior among USB, `VIN`, and battery
- Total current consumption in boot, idle, storage, video, and audio modes
- GPIO drive and input thresholds as exposed by each connector
- Validated QSPI, PSRAM, SDIO, PDM, I2C, and HSTX operating rates
- Board-level temperature, humidity, ESD, and thermal performance

### **2.6 Electrical Precautions** {.section-page}

1. Begin first power-up from a current-limited USB source.
2. Connect ground before external clocks, data, or analog signals.
3. Do not connect a battery without documented polarity, chemistry, voltage,
   connector, and charge-current compatibility.
4. Do not power the 3.3 V rail simultaneously from the board regulator and an
   external source unless that operating mode is explicitly approved.
5. Do not share GPIO12–GPIO19 with other driven circuits while HSTX video is
   active.
6. Remove power before changing FFC/FPC, microSD, or battery connections.
