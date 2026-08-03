## **1 The Board**

The UNIT PULSAR RP2350 is a development board for evaluating the
Raspberry Pi RP2350A and building applications that combine high-speed digital
output, removable storage, motion sensing, digital audio, external memory, and
general-purpose I/O. The V1.3.0 artwork places the controller, QSPI flash,
PSRAM, power components, indicators, and user controls on the top side. The
microSD socket, battery connection, onboard microphone, debug pads, and HSTX
connector are accessible from the bottom side.

### **1.1 Accessories** {.section-page}

The source package does not define an accessory bundle. The following items
support board operation but are not claimed as package contents:

| Accessory | Purpose | Selection notes |
|---|---|---|
| USB-C data cable | Power, programming, and USB serial | Must support data; a charge-only cable cannot upload firmware |
| SWD probe | Low-level programming and debug | Use 3.3 V-compatible SWDIO, SWCLK, GND, and target reference |
| microSD card | Filesystem and data-logging examples | Wiki examples expect a FAT32-formatted card |
| QWIIC cable and sensor | External I2C expansion | Match the connector pitch, contact order, orientation, and 3.3 V domain |
| HSTX display adapter/cable | DVI-compatible video experiments | Must match the 22-position, 0.5 mm connector and routed TMDS pairs |
| Single-cell battery | Battery-powered operation | Requires documented chemistry, polarity, connector fit, voltage, and charge-current compatibility |
| Logic analyzer or oscilloscope | Interface bring-up | Useful for I2C, SPI/SDIO, PDM, and clock verification |

Accessories must not be selected only from a connector's mechanical
appearance. Verify pitch, contact orientation, polarity, voltage domain, and
pin order against the controlled assembly information.

### **1.2 Board Identification**

| Item | Value |
|---|---|
| Product | UNIT PULSAR RP2350 |
| Product family | UNIT DevLab ecosystem |
| Product type | Multi-interface RP2350A development board |
| Manufacturer Part Number | UE0103 |
| Main component | Raspberry Pi RP2350A, QFN-60 |
| Hardware artwork | V1.3.0 |
| Product Reference | Version 0.1.0 |
| Primary programming interface | USB-C / RP2350 USB boot workflow |
| Debug interface | SWD pads on bottom side |

The Manufacturer Part Number identifies the manufacturing assembly; it is not
the commercial product name. Hardware revision and documentation revision are
controlled independently.

### **1.3 Main Assemblies**

| RefDes | Fitted component | Function |
|---|---|---|
| IC3 | RP2350A | Main processor and peripheral controller |
| IC1 | W25Q128JVPIQ | 128 Mbit (16 MiB) external QSPI flash |
| IC4 | APS6404L-3SQR-ZR | 8 MiB external PSRAM |
| IC5 | BMI270 | Six-axis accelerometer and gyroscope |
| MK1 | ICS-41350 | Digital PDM microphone |
| U1 | AP2112K-3.3TRG1 | Fixed 3.3 V LDO |
| IC2 | MCP73831T-2ACI/OT | Single-cell Li-Ion/Li-Polymer charge controller |
| XTAL1 | XOS20012000LT00351005 | 12 MHz reference oscillator |
| MICRO_SD-HOLDER | 47309-2651 | Removable microSD storage |
| LED1–LED3 | WS2812 1010 | Cascaded addressable RGB indicators |
| J1 | HCZZ0032-4 | Four-position QWIIC-style I2C connector |
| J5 | FH34SRJ-22S-0.5SH(50) | 22-position HSTX FFC/FPC connector |
| JP1 | PH2.0 2P | Two-position battery connection |

### **1.4 Board Views** {.section-page}

![](hardware/resources/unit_top_v_1_3_0_pulsar_rp2350a.png){width=3.2in}

The top view identifies the USB-C connector, BOOT and reset controls, edge-pad
labels, RP2350A, flash, PSRAM, QWIIC connector, oscillator, and three RGB LEDs.

![](hardware/resources/unit_btm_v_1_3_0_pulsar_rp2350a.png){width=3.2in}

The bottom view identifies the battery polarity marks, microSD socket, onboard
microphone, SWD pads, HSTX connector, and V1.3.0 artwork marking.

### **1.5 Package Contents and Handling** {.section-page}

The available documentation defines the assembled board but does not specify
an accessory bundle or package-contents list.

Handle the board using normal ESD precautions. Avoid touching the microphone
port, connector contacts, or exposed test pads. Remove power before inserting
or removing FFC/FPC and battery connectors. Keep conductive objects away from
the bottom-side battery and microSD areas when the board is energized.
