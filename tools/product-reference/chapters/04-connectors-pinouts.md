## **4 Connectors and Pinout**

### **4.1 Edge Connections**

| Board label | RP2350A connection | Function / status |
|---|---|---|
| `TX0` / `D1` | GPIO18 | Digital I/O / UART-capable |
| `RX0` / `D0` | GPIO19 | Digital I/O / UART-capable |
| `D2`, `D3`, `D4`, `D5`, `D6`, `D7` | GPIO17, 16, 15, 14, 13, 12 | Digital I/O; also routed to HSTX connector |
| `D8`, `D9` | Pending | Artwork labels exist; schematic shows no RP2350A connection |
| `D10` / `SS` | GPIO21 | Digital I/O |
| `D11` / `MOSI` | GPIO22 | Digital I/O |
| `D12` / `MISO` | GPIO23 | Digital I/O |
| `D13` / `SCK` / LED | GPIO20 | Digital I/O and user indicator |
| `A1` / `D15` | GPIO29 / ADC3 | Analog-capable digital I/O |
| `A2` / `D16` | GPIO27 / ADC1 | Analog-capable digital I/O |
| `A3` / `D17` | GPIO26 / ADC0 | Analog-capable digital I/O |
| `SDA` / `D18` | GPIO8 | Internal/user I2C data |
| `SCL` / `D19` | GPIO9 | Internal/user I2C clock |
| `D21` | GPIO10 | PDM clock net |
| `RGB` | GPIO1 | WS2812 data |
| `3V3`, `3EN`, `VBAT`, `VUSB`, `VIN` | Power | See Section 2; operating limits pending |
| `RST` | Reset | RP2350A reset control |
| `GND` | Ground | Common return |

### **4.2 Fixed Peripheral Mapping**

| Peripheral | Signal mapping |
|---|---|
| PSRAM | CS=GPIO0; data/clock on the schematic QSPI nets |
| microSD | CLK=GPIO2, CMD=GPIO3, DAT0=GPIO4, DAT1=GPIO5, DAT2=GPIO6, DAT3=GPIO7 |
| BMI270 | SDA=GPIO8, SCL=GPIO9 |
| PDM microphone | CLK=GPIO10, DATA=GPIO11 |
| HSTX signal group | GPIO12 through GPIO19 |
| QWIIC | SDA=GPIO24, SCL=GPIO25, 3.3 V, GND |
| RGB LED chain | DATA=GPIO1 |

### **4.3 QWIIC Connector**

J1 is a four-position, 1 mm-pitch right-angle connector. The schematic shows
GND, 3.3 V, GPIO24/SDA, and GPIO25/SCL. A controlled contact-number/orientation
drawing and compatible cable specification are pending validation.

### **4.4 HSTX Connector**

J5 is a 22-position, 0.5 mm-pitch FFC/FPC connector. It exposes D0–D7,
A0/GPIO28, A1/GPIO29, GPIO24/SDA, GPIO25/SCL, 3.3 V, and return positions. Use
the released schematic for prototype tracing; the complete controlled connector
pin-number table remains pending validation.

### **4.5 Programming and Battery Connections**

The bottom artwork shows SWDIO, SWCLK, 3.3 V, and GND programming pads. JP1 is
a two-position battery connection. Battery polarity is marked on the artwork,
but a compatible battery/cable assembly is not specified by this preview.
