## **3 Functional Overview**

The UNIT PULSAR RP2350 is organized around the RP2350A processor, with dedicated
external memories and fixed onboard peripherals. Firmware can use each block
independently or combine acquisition, storage, user feedback, and video in one
application.

### **3.1 Block Diagram** {.section-page}

![](hardware/resources/unit_block_v_1_0_0_ue0103_pulsar_rp2350a.jpg){width=7.0in}

The RP2350A controls every data path. W25Q128 flash stores executable code and
nonvolatile application data. PSRAM extends working memory. The microSD socket
provides removable storage. BMI270 and ICS-41350 devices provide motion and
audio input. QWIIC and edge pads expose expansion signals, while HSTX and the
LEDs provide high-speed and visual outputs.

### **3.2 Board Topology** {.section-page}

![](hardware/resources/unit_topology_v1_3_0_ue0103_pulsar_rp2350a.png){width=7.0in}

| RefDes | Component | Confirmed role |
|---|---|---|
| IC3 | RP2350A | Main microcontroller |
| IC1 | W25Q128JVPIQ | 128 Mbit (16 MiB) QSPI flash memory |
| IC4 | APS6404L-3SQR-ZR | 8 MiB external PSRAM |
| IC5 | BMI270 | Six-axis IMU connected to the internal I2C bus |
| MK1 | ICS-41350 | Digital PDM MEMS microphone |
| U1 | AP2112K-3.3TRG1 | Fixed 3.3 V LDO regulator |
| IC2 | MCP73831T-2ACI/OT | Single-cell Li-Ion/LiPo battery charge controller |
| XTAL1 | 12 MHz oscillator | RP2350A reference clock source |
| L1 | 3.3 µH inductor | RP2350A internal switching-regulator inductor |
| MICRO_SD_HOLDER | 47309-2651 | microSD card socket connected through four-bit SDIO signals |
| LED1–LED3 | XL-1010RGBC-WS2812B | Cascaded addressable RGB LEDs |
| J1 | HCZZ0032-4 | Four-position, 1 mm pitch QWIIC connector |
| J2 | USB-C connector | USB power, programming, and USB data interface |
| JP1 | Battery connector | Two-position single-cell LiPo battery connection |
| J5 | FH34SRJ-22S-0.5SH(50) | 22-position, 0.5 mm pitch FFC/FPC connector for HSTX video and auxiliary signals |
| S2 | BOOT switch | Forces RP2350A USB boot mode during startup/reset |
| JP2 | Castellated header row | Left-side GPIO, power, analog, and digital expansion |
| JP3 | Castellated header row | Right-side GPIO, power, analog, and digital expansion |
| EN_PAD | Solder jumper | Connects the AP2112K enable signal to the castellated header, allowing external control of the 3.3 V regulator |
| VBAT_PAD | Solder jumper | Connects the VBAT rail to the castellated header, providing access to the battery supply |
| INT_PAD | Solder jumper | Connects the BMI270 interrupt signal to the RP2350A GPIO, enabling hardware interrupt operation |
| RGB_PAD | Solder jumper | Connects the data output of the third onboard NeoPixel to the castellated header, allowing the RGB chain to be extended with external NeoPixels |
| SWDIO | Debug test pad | RP2350A Serial Wire Debug data signal |
| SWCLK | Debug test pad | RP2350A Serial Wire Debug clock signal |
| GND | Debug test pad | Ground reference for the SWD interface |

The top side groups programming, processing, memory, and user-visible controls.
USB-C, BOOT, reset, QSPI flash, PSRAM, RP2350A, QWIIC, and RGB indicators are
visible from this side. The bottom side groups removable storage, battery,
audio, SWD, and HSTX connections.

| Board region | Main elements | Design intent |
|---|---|---|
| USB end | USB-C, BOOT, reset, power/charge indicators | Programming and initial power-up |
| Upper center | power-path devices and PSRAM | Source routing and working-memory expansion |
| Center | RP2350A and 12 MHz oscillator | Processing and clock generation |
| Lower center | QSPI flash and PDM microphone area | boot storage and audio acquisition |
| QWIIC end | three RGB LEDs and QWIIC connector | status display and external I2C |
| Bottom side | battery, microSD, BMI270, SWD, HSTX | storage, sensing, debug, and video expansion |

The two edge-pad rows expose power, analog, serial, and general-purpose
signals. Some HSTX-routed signals are shared with edge positions, so firmware
ownership must be decided before enabling high-speed video.

### **3.3 Processor** {.section-page}

RP2350A is the main controller. According to the Raspberry Pi component
datasheet, the device provides two selectable processor architectures: dual
Arm Cortex-M33 or dual Hazard3 RISC-V cores, with a nominal system frequency up
to 150 MHz. Firmware selects one architecture for a given build; it does not
execute Arm and RISC-V code simultaneously.

![Raspberry Pi RP2350A QFN-60 microcontroller](hardware/resources/unit_rp2350a_qfn60_package_pulsar_rp2350.jpg){width=3.5in}

The processor integrates 520 kB of on-chip SRAM arranged in ten banks, USB 1.1
host/device control with an embedded PHY, ADC inputs shared with GPIO, fixed
serial peripherals, PWM, DMA, three PIO blocks with twelve state machines, and
one HSTX peripheral. The PULSAR design routes a selected subset of these
functions to onboard devices and external connectors.

The on-chip SRAM is the lowest-latency working memory. It contains stacks,
heaps, interrupt data, time-critical buffers, and code copied from flash when a
framework requires it. DMA and multicore applications must coordinate access
to shared buffers and peripherals.

### **3.4 Memory Architecture: Flash and PSRAM** {.section-page}

The W25Q128JVPIQ provides 128 Mbit (16 MiB) of external QSPI flash. It stores
the boot image, application firmware, and any filesystem or data region defined
by the selected board-package partition scheme. The BOOT control participates
in the RP2350 USB boot workflow used to load recovery or update images.

The APS6404L-3SQR-ZR provides 8 MiB of external PSRAM with chip select on
GPIO0. In the Arduino workflow, the board configuration must set PSRAM CS to
GPIO0 and select the 8 MiB capacity. Static objects can be placed in PSRAM with
the core's `PSRAM` attribute; dynamic objects can be allocated with `pmalloc()`
and released with `free()`.

![External PSRAM location](hardware/resources/unit_wiki_psram_pulsar_rp2350.png){width=5.2in}

PSRAM is suited to framebuffers, file buffers, captured audio, sensor history,
and large application structures. Interrupt flags, frequently accessed state,
and timing-critical data should remain in internal SRAM. The application must
check allocation results and avoid assuming that all configured PSRAM remains
free after global/static allocations.

### **3.5 HSTX Video Output** {.section-page}

The HSTX peripheral serializes data at high speed and can generate the
pseudo-differential TMDS signals used by DVI-compatible displays. The wiki and
PCB routing define four channel pairs:

![HSTX connector location](hardware/resources/unit_wiki_hstx_pulsar_rp2350.png){width=6.2in}

| TMDS channel | Positive GPIO | Negative GPIO | Function |
|---|---:|---:|---|
| Clock | 14 | 15 | Pixel/link clock pair |
| Data 0 | 18 | 19 | TMDS data channel 0 |
| Data 1 | 16 | 17 | TMDS data channel 1 |
| Data 2 | 12 | 13 | TMDS data channel 2 |

The 22-position HSTX connector carries these signals and returns. The wiki uses
the UDVI HSTX library with a 320 × 240 RGB565 framebuffer, drawing primitives,
text, and partial-screen updates. This resolution is an implementation profile
from the wiki, not a limit of the connector or RP2350A.

![UDVI HSTX library in Arduino Library Manager](hardware/resources/unit_wiki_udvi_library_pulsar_rp2350.png){width=2.1in}

While HSTX is enabled, GPIO12–GPIO19 are actively driven and must not be shared
with another output or an attached circuit that drives the same nets. Display
adapters must match the connector contact order and differential-pair routing.

### **3.6 MicroSD Card Socket** {.section-page}

The onboard 47309-2651 microSD socket is connected to a complete four-bit SDIO signal group and operates in the 3.3 V logic domain.

![microSD socket location](hardware/resources/unit_wiki_microsd_pulsar_rp2350.png){width=5.2in}

| Signal | GPIO | SPI-mode role in current examples |
|---|---:|---|
| `SDIO_CLK` | 2 | SCK |
| `SDIO_CMD` | 3 | MOSI |
| `SDIO_DAT0` | 4 | MISO |
| `SDIO_DAT1` | 5 | Not used by SPI mode |
| `SDIO_DAT2` | 6 | Not used by SPI mode |
| `SDIO_DAT3` | 7 | Chip select |

The provided examples use the SPI-compatible subset through `SPI` and `SDFS` for initialization, file creation, reading, directory enumeration, and data logging.

Software with four-bit SDIO support can additionally use DAT1 and DAT2. File writes should be flushed and closed before card extraction or power removal.

Card capacity, speed class, and filesystem support depend on the software environment. FAT32 is recommended for the provided examples.

### **3.7 LED Indicators** {.section-page}

Three XL-1010RGBC-WS2812B addressable RGB LEDs form a serial chain driven by GPIO1. Firmware transmits an ordered color frame through the chain, allowing the three onboard pixels to provide status indication, progress animation, and user feedback from a single GPIO.

![WS2812 RGB LED locations](hardware/resources/unit_wiki_ws2812_pulsar_rp2350.png){width=5.8in}

The `RGB_PAD` solder jumper can connect the data output of the third onboard RGB LED to the castellated header. When this jumper is closed, the onboard RGB chain can be extended with compatible external addressable RGB LEDs.

The board also includes a user indicator on GPIO22 (`D13` / `BUILTIN1`), a power indicator, and a battery charge-status indicator. The user LED and RGB LEDs are firmware-controlled. The power indicator follows the corresponding power rail, while the charge-status indicator is controlled by the MCP73831 `STAT` output.

![Built-in user LED location](hardware/resources/unit_wiki_led_builtin_pulsar_rp2350.png){width=5.2in}

Applications should limit RGB brightness when power consumption or thermal rise is important. RGB LED control is independent of the HSTX video interface.

### **3.8 AP2112K and MCP73831 Power Management System** {.section-page}

U1 is an AP2112K fixed 3.3 V LDO regulator. It converts the `VSYS` rail into the regulated 3.3 V logic domain used by the RP2350A, external memories, sensors, indicators, microSD interface, and QWIIC connector. The regulator supports up to 600 mA total output current, shared between the onboard circuitry and any external load connected to the 3.3 V rail.

The AP2112K `EN` signal controls the 3.3 V regulator. The `EN_PAD` solder jumper allows this signal to be routed to the castellated header, providing external control of the regulator enable function when the jumper is closed.

IC2 is an MCP73831T-2ACI/OT single-cell Li-Ion/LiPo battery charge controller. Hardware V1.3.0 is configured for a nominal charge current of 200 mA. The charge current is established by the PROG resistor and may be modified by changing this resistor according to the MCP73831 configuration requirements.

The battery input is intended for a single-cell LiPo battery with a nominal voltage of 3.7 V and a maximum fully charged voltage of 4.2 V. The battery path includes reverse-polarity protection.

The `VBAT_PAD` solder jumper allows the battery rail to be connected to the castellated header. When closed, the battery voltage can be accessed directly from the corresponding header position for external circuitry.

The board power-path circuitry combines USB, `VIN`, battery, `VSYS`, and the regulated 3.3 V domain. Schottky diodes and MOSFETs provide source routing and battery protection according to the implemented hardware design.

### **3.9 Power Tree** {.section-page}

![](hardware/resources/unit_power_tree_v_1_0_0_ue0103_pulsar_rp2350a.jpg){width=7.0in}

The power tree summarizes the main supply domains and their relationship within the UNIT PULSAR RP2350A. It is intended as a functional reference and does not replace the complete schematic.

The board can be powered from USB-C, `VIN`, or a single-cell LiPo battery. These sources are routed through the onboard power-path circuitry to the `VSYS` domain. The AP2112K-3.3 then generates the regulated 3.3 V rail used by the RP2350A and onboard peripherals.

The 3.3 V rail is also available through the castellated headers and QWIIC connector. The AP2112K provides up to 600 mA total output current. This current is shared between the RP2350A, memories, sensors, LEDs, microSD interface, and externally connected 3.3 V devices.

The current available to external loads therefore depends on the active onboard circuitry and application workload. The total 3.3 V load must remain within the regulator output capability.

The `VBAT_PAD` and `EN_PAD` solder jumpers provide optional access to the battery rail and regulator-enable control through the castellated headers.

### **3.10 BMI270 Motion Sensor** {.section-page}

The onboard BMI270 combines a three-axis accelerometer and three-axis gyroscope. It is connected to GPIO8 (`SDA`) and GPIO9 (`SCL`) on the internal I2C bus. Firmware can detect the sensor through its supported I2C address configuration and read acceleration and angular-rate data.

The `INT_PAD` solder jumper provides an optional hardware interrupt connection between the BMI270 and GPIO12 of the RP2350A. When the jumper is closed, BMI270 interrupt events can be routed directly to GPIO12 for interrupt-driven applications without continuous polling.

Typical applications include orientation interfaces, motion-triggered logging, gesture input, vibration monitoring, and motion-controlled graphics or user interfaces.

Measurement range, filtering, output data rate, interrupt source, and interrupt behavior are configured through the BMI270 registers or software driver and are not fixed by the PCB.

### **3.11 PDM Microphone** {.section-page}

The ICS-41350 is an onboard digital MEMS microphone. RP2350A supplies its PDM
clock on GPIO10 and receives the one-bit data stream on GPIO11. The software PDM
stack clocks the microphone, decimates the stream, and produces PCM sample
buffers for analysis, visualization, streaming, or storage.

![PDM microphone location](hardware/resources/unit_wiki_pdm_pulsar_rp2350.png){width=5.5in}

The acoustic port must remain unobstructed. Enclosures, adhesive, contamination,
and board mounting can affect acoustic performance. Board-level sensitivity,
noise, frequency response, and enclosure behavior depend on the mechanical and
acoustic implementation and are not specified at module level.

### **3.12 I2C and QWIIC Expansion** {.section-page}

The board provides two distinct I2C routes. GPIO8/GPIO9 serve the onboard
BMI270 and are also represented by `SDA`/`SCL` edge labels. GPIO24/GPIO25 feed
the four-position QWIIC connector and HSTX connector positions.

![I2C and QWIIC connections](hardware/resources/unit_wiki_i2c_pulsar_rp2350.png){width=6.2in}

This separation lets an application keep the IMU bus independent from external
QWIIC sensors. The wiki includes bus scanning, BMI270 access, EEPROM byte and
block operations, hexadecimal dumps, and structured EEPROM records. External
pull-ups, device addresses, bus capacitance, and cable length must be considered
when attaching multiple devices.

### **3.13 Combined System Operation** {.section-page}

The board is designed for concurrent use of its subsystems. For example, the
BMI270 can control an HSTX-rendered object while PSRAM holds large graphics or
history buffers; the microphone or an I2C sensor can produce records stored on
microSD; and RGB LEDs can show acquisition, storage, or fault state.

A robust application initializes one subsystem at a time, checks every return
value, keeps high-rate and interrupt data in internal SRAM, moves large buffers
to PSRAM, flushes storage before shutdown, and yields enough execution time for
USB and framework services. The repository's C++ examples implement each stage
separately before the combined application.
