## **3 Functional Overview**

### **3.1 Processing and Boot Memory**

The RP2350A is the central controller for the board and provides the GPIO,
ADC, I2C, PIO, USB, and HSTX resources used by the onboard subsystems. Program
storage is provided by the external W25Q128JVPIQ QSPI flash, with a capacity of
128 Mbit (16 MiB). The BOOT pushbutton controls the flash boot-selection path,
and the reset control restarts the RP2350A without removing board power.

The board is intended to be programmed through USB-C using the UNIT
RP2040/RP2350 board package or another RP2350-compatible toolchain. The wiki
uses the user LED as the first upload and execution check before enabling the
remaining peripherals.

### **3.2 Internal and External Memory**

The RP2350A provides 520 KiB of internal SRAM for low-latency program data. An
APS6404L-3SQR-ZR adds 8 MiB of external PSRAM for framebuffers, acquisition
buffers, large arrays, and other data that would otherwise consume internal
SRAM. Its chip-select is connected to GPIO0.

In the Arduino workflow described by the wiki, selecting `PSRAM CS = GPIO 0`
enables the board definition to initialize this memory. Applications can then
place static buffers in PSRAM or request dynamic allocations from its heap.
Time-critical data can remain in internal SRAM while display buffers, logged
data, and other large objects are kept in PSRAM.

### **3.3 Motion Sensing and I2C Expansion**

The onboard BMI270 six-axis IMU uses the internal I2C pair on GPIO8 (`SDA`) and
GPIO9 (`SCL`). Firmware reads its accelerometer and gyroscope data over this
bus for motion, orientation, and user-interface applications.

The QWIIC connector provides a separate I2C path on GPIO24 (`SDA`) and GPIO25
(`SCL`), together with 3.3 V and GND. This allows external sensors, EEPROMs,
and other I2C peripherals to operate without taking over the BMI270 bus. The
wiki documents scanning and device access on both available I2C pin pairs.

### **3.4 microSD Storage**

The microSD socket is electrically connected to GPIO2–GPIO7 as `CLK`, `CMD`,
and `DAT0`–`DAT3`, allowing the RP2350A to use the complete four-bit SDIO signal
group. The current wiki examples use the SPI-compatible subset:

| microSD operation | GPIO | Schematic signal |
|---|---:|---|
| Clock | 2 | `SDIO_CLK` |
| Command / MOSI | 3 | `SDIO_CMD` |
| Data / MISO | 4 | `SDIO_DAT0` |
| Chip select in SPI mode | 7 | `SDIO_DAT3` |

This arrangement supports filesystem operations such as card initialization,
file creation, reading, directory listing, and sensor-data logging. GPIO5 and
GPIO6 provide `DAT1` and `DAT2` when software uses the full four-bit SDIO bus.

### **3.5 HSTX Video Output**

The RP2350A HSTX peripheral can serialize display data into four
pseudo-differential TMDS channel pairs for DVI-compatible video. The wiki
defines the routed pair order as follows:

| TMDS channel | Positive GPIO | Negative GPIO |
|---|---:|---:|
| Clock | 14 | 15 |
| Data 0 | 18 | 19 |
| Data 1 | 16 | 17 |
| Data 2 | 12 | 13 |

These GPIOs are available through the 22-pin HSTX connector. When video output
is active, the eight pins are driven as a group and must be treated as reserved
for that function. The wiki describes a 320 × 240 RGB565 framebuffer workflow,
drawing primitives, text rendering, and partial-screen updates; PSRAM is
available for large application buffers where supported by the display stack.

### **3.6 PDM Audio Input**

The onboard ICS-41350 converts acoustic pressure into a one-bit PDM data
stream. The RP2350A supplies the microphone clock on GPIO10 and receives data
on GPIO11. A PDM-capable software peripheral decimates this stream into signed
PCM samples that can be processed, displayed, or stored on microSD.

The microphone is already connected on the PCB; no external audio wiring is
required for onboard capture. Sample rate, buffering, filtering, and storage
format are selected by the application software.

### **3.7 Visual Indicators and User Feedback**

Three cascaded WS2812-compatible RGB LEDs share a single data input on GPIO1.
Because the LEDs are connected as a serial chain, firmware sends one ordered
color frame to update all three devices. They can provide status, progress,
alerts, or application-specific color feedback.

The board also includes a GPIO20 user indicator (`D13` / `BUILTIN1`), a power
indicator, and a charge-status indicator. The RGB chain and user LED are
independently controlled.

### **3.8 Power Distribution and Battery Support**

USB VBUS, `VIN`, and the battery circuit feed the board power path. The
AP2112K-3.3TRG1 generates the 3.3 V rail used by the RP2350A and onboard
peripherals. The MCP73831 provides the single-cell battery-charging function,
with the charge indicator reporting the controller status. Schottky diodes and
MOSFETs implement the source-routing and protection paths shown in the
schematic.

The hardware design is complete and awaiting fabrication. Final module-level
input ranges, available rail current, charge configuration, and source-priority
behavior will be confirmed on the first manufactured units.

### **3.9 Combined System Operation**

The subsystems are intended to operate together: the BMI270 or PDM microphone
can provide acquisition data, PSRAM can hold large working buffers, microSD can
store results, the RGB LEDs can report state, and HSTX can present a graphical
interface. The wiki's complete-application chapter combines motion sensing and
video output and describes moving large buffers out of internal SRAM to keep
the RP2350A responsive.

![](hardware/resources/unit_btm_v_1_3_0_pulsar_rp2350a.png){width=3.0in}
