# UNIT PULSAR RP2350 C++ Examples

This directory contains the complete Arduino C++ sketches described by the
PULSAR RP2350 technical wiki. The examples implement the design-defined pin
mapping and document the required framework and library interfaces.

Each sketch is stored in a directory with the same name as its `.ino` file so
it can be opened directly with Arduino IDE or compiled with Arduino CLI.

## Toolchain Setup

1. Install Arduino IDE 2.x or Arduino CLI.
2. Add the UNIT board-package index:
   `https://raw.githubusercontent.com/UNIT-Electronics/Uelectronics-RP2040-Arduino-Package/main/package_Uelectronics_rp2040_index.json`
3. Select **Generic RP2350** or the PULSAR RP2350 board definition when it is
   available.
4. Configure 16 MiB flash and set **PSRAM CS = GPIO 0**, **PSRAM size = 8 MiB**.
5. Compile and upload one sketch at a time.

## Required Libraries

| Examples | Dependency |
|---|---|
| WS2812 | Adafruit NeoPixel |
| BMI270 and combined application | SparkFun BMI270 Arduino Library |
| microSD | `SPI` and `SDFS` from the UNIT RP2040/RP2350 core |
| HSTX video and combined application | UDVI HSTX |
| PDM microphone | `PDM` from the UNIT RP2040/RP2350 core |

`Arduino.h`, `Wire`, and the RP2350 PSRAM allocation functions are supplied by
the selected board core.

## Example Index

| Wiki chapter | Directory | Complete sketches | Purpose |
|---|---|---:|---|
| Blinking LED | `01_blink_led/` | 2 | Basic user LED and serial-debug blink |
| ADC Basics | `02_adc/` | 2 | Analog acquisition and threshold output |
| WS2812B | `03_ws2812/` | 3 | RGB sequence, brightness, and running pixel |
| I2C Communication | `04_i2c/` | 7 | Bus scan, BMI270, and external EEPROM operations |
| microSD | `05_microsd/` | 4 | Initialization, read/write, directory listing, and logging |
| HSTX Video | `06_hstx/` | 3 | Test pattern, graphics primitives, and system monitor |
| Complete Application | `07_complete_application/` | 1 | BMI270-controlled 3D cube over HSTX |
| PSRAM Memory | `08_psram/` | 5 | Detection, static/dynamic allocation, test, and monitoring |
| PDM Microphone | `09_pdm/` | 1 | Onboard PDM capture and serial PCM output |
| **Total** |  | **28** |  |

## Board Connections Used

| Subsystem | GPIO mapping |
|---|---|
| RGB LED chain | GPIO1 |
| microSD SPI subset | SCK=GPIO2, MOSI/CMD=GPIO3, MISO/DAT0=GPIO4, CS/DAT3=GPIO7 |
| BMI270 I2C | SDA=GPIO8, SCL=GPIO9 |
| PDM microphone | CLK=GPIO10, DATA=GPIO11 |
| HSTX TMDS | Clock=GPIO14/15, Data0=GPIO18/19, Data1=GPIO16/17, Data2=GPIO12/13 |
| External PSRAM | CS=GPIO0 |
| User LED | GPIO20 (`D13` / `BUILTIN1` in the V1.3 schematic) |

The microSD hardware includes the full `DAT0`–`DAT3` SDIO group. The repository
wiki sketches operate the socket in SPI mode using the compatible subset shown
above.

## Supplementary Wiki Notes

The wiki also contains short, non-standalone fragments illustrating EEPROM
write delays, closing and flushing files, partial HSTX screen updates, PSRAM
placement, multicore display updates, low-memory behavior, and watchdog use.
These fragments depend on symbols from their surrounding sketches and are not
duplicated as independent `.ino` files because they would not compile alone.
They remain available in the corresponding chapters of the
[PULSAR RP2350 technical wiki](https://github.com/UNIT-Electronics-MX/unit_pulsar_rp2350a/wiki).

## Source Notes

The files preserve the complete code blocks from the wiki, add a source header,
and reconcile the user LED with the V1.3 schematic (`GPIO20`). Compile
validation checks syntax and library compatibility. Runtime behavior depends
on the selected core, libraries, peripherals, and application configuration.
