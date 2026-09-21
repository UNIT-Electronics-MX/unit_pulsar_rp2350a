## **1 The Board**

The UNIT PULSAR RP2350 is a development board for evaluating the
Raspberry Pi RP2350A and building applications that combine high-speed digital
output, removable storage, motion sensing, digital audio, external memory, and
general-purpose I/O. Hardware revision V1.3.0 places the controller, QSPI flash,
PSRAM, power components, indicators, and user controls on the top side. The
microSD socket, battery connection, onboard microphone, debug pads, and HSTX
connector are accessible from the bottom side.

### **1.1 Accessories** {.section-page}

The UNIT PULSAR RP2350A includes a QWIIC cable for connecting compatible I2C devices. Additional accessories are available depending on the application.

| Accessory | Included | Purpose | Selection notes |
|---|---|---|---|
| QWIIC cable | Yes | External I2C expansion | Included with the board; compatible with 3.3 V QWIIC devices |
| USB-C data cable | No | Power, programming, and USB serial | Must support data; a charge-only cable cannot upload firmware |
| Kingston microSD card | No | Removable storage and data logging | FAT32 formatting is recommended for the provided examples |
| UNIT DevLab DVI to FPC Adapter | No | HSTX DVI-compatible video output | Recommended adapter for connecting the HSTX video interface |
| 22-pin FPC cable | No | Connection between the HSTX interface and DVI adapter | 22-position, 0.5 mm pitch; available soon from UNIT Electronics |
| LiPo 3.7 V 650 mAh Battery | No | Battery-powered operation | Recommended single-cell LiPo battery; verify polarity and connector orientation before connection |

Verify connector type, orientation, polarity, voltage domain, and pinout before connecting third-party accessories.

### **1.2 Board Identification**

| Item | Value |
|---|---|
| Product | UNIT PULSAR RP2350 |
| Product family | UNIT DevLab ecosystem |
| Product type | Multi-interface RP2350A development board |
| Main component | Raspberry Pi RP2350A, QFN-60 |
| Hardware revision | V1.3.0 |
| Product Reference | Version 0.1.0 |
| Primary programming interface | USB-C / RP2350 USB boot workflow |
| Debug interface | SWD pads on bottom side |

Hardware revision and documentation revision are identified independently.

### **1.3 Main Assemblies**

| RefDes | Component | Function |
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
microphone, SWD pads, HSTX connector, and V1.3.0 revision marking.

### **1.5 Handling** {.section-page}

Handle the board using normal ESD precautions. Avoid touching the microphone
port, connector contacts, or exposed test pads. Remove power before inserting
or removing FFC/FPC and battery connectors. Keep conductive objects away from
the bottom-side battery and microSD areas when the board is energized.
