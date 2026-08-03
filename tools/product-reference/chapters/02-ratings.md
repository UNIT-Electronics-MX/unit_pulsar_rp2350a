## **2 Electrical Characteristics**

### **2.1 Confirmed Component and Rail Values**

| Parameter | Value | Scope / evidence |
|---|---:|---|
| Regulated board rail | 3.3 V nominal | AP2112K-3.3TRG1 output shown in schematic and BOM |
| USB supply net | +5 V nominal | USB-C VBUS net label in schematic |
| External flash capacity | 128 Mbit (16 MiB) | W25Q128JVPIQ part identification |
| External PSRAM capacity | 8 MiB | APS6404L-3SQR-ZR schematic annotation and BOM |
| RP2350 internal SRAM | 520 KiB | RP2350 component datasheet |
| RP2350 nominal maximum system clock | 150 MHz | RP2350 component datasheet; not a module test result |
| Board oscillator | 12 MHz | XTAL1 schematic and BOM |
| PDM microphone supply range | 1.65 to 3.63 V | ICS-41350 BOM description; component rating only |

The 3.3 V rail, USB net label, microphone supply range, and individual power
component ratings do not establish complete board ratings.

### **2.2 Pending Module-Level Characteristics**

- Allowed `VIN` and `VBAT` operating and absolute-maximum ranges
- 3.3 V rail output current available to external loads
- USB, battery, and `VIN` source-selection behavior under all conditions
- Battery charge current and compatible cell/cable specification
- GPIO thresholds, drive limits, and mixed-supply behavior at board connectors
- Total current consumption and thermal limits
- Validated SDIO, HSTX, PDM, PSRAM, and QSPI clock rates

### **2.3 Electrical Precautions**

- Do not infer a board input limit from the AP2112K or MCP73831 component rating.
- Do not attach a battery until polarity, chemistry, connector fit, and charge
  settings have been validated for the assembly.
- Connect a common ground before applying external signals.
- Treat all exposed I/O as belonging to the 3.3 V RP2350A domain unless a
  released board specification states otherwise; tolerance to other levels is
  pending validation.
