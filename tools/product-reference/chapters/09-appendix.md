## **9 Appendix**

### **9.1 Schematic** {.section-page}

The following three sheets are rendered from `unit_sch_v_1_3_0_pulsar_rp2350a.pdf`. The original PDF remains the authoritative electrical schematic for hardware revision V1.3.0.

<div class="schematic-page">

#### **9.1.1 Processor, Memory, USB, I/O, and Power Entry**

![](hardware/resources/unit_schematic_v_1_3_0_pulsar_rp2350a_sheet_1.png){width=7.2in}

</div>

<div class="schematic-page">

#### **9.1.2 microSD, BMI270, HSTX Connector, and PDM Microphone**

![](hardware/resources/unit_schematic_v_1_3_0_pulsar_rp2350a_sheet_2.png){width=7.2in}

</div>

<div class="schematic-page">

#### **9.1.3 3.3 V Regulator and Battery Protection**

![](hardware/resources/unit_schematic_v_1_3_0_pulsar_rp2350a_sheet_3.png){width=7.2in}

</div>

### **9.2 Technical References** {.section-page}

The documentation set for the UNIT PULSAR RP2350A is organized around the following technical sources:

1. The hardware V1.3.0 schematic defines board connectivity, component designators, power architecture, and electrical implementation.

2. The official Raspberry Pi RP2350 datasheet defines RP2350A device-level electrical characteristics, processor capabilities, GPIO behavior, ADC operation, and HSTX functionality.

3. The UNIT Electronics Wiki provides setup procedures, peripheral usage documentation, application examples, and software workflows.

4. The repository C++ examples provide implementation references for the board peripherals and supported software APIs.

### **9.3 Design and Application Notes** {.section-page}

The following characteristics depend on the final application, firmware configuration, connected peripherals, or mechanical integration:

- Total board current consumption varies with processor activity, clock configuration, enabled peripherals, RGB LED brightness, microSD activity, PDM audio acquisition, PSRAM usage, HSTX video output, and external loads.
- Available current for external 3.3 V devices depends on the portion of the AP2112K 600 mA output capability consumed by the board itself.
- Maximum validated interface rates may depend on firmware configuration, connected devices, cable characteristics, and signal integrity.
- Final microphone acoustic performance depends on enclosure geometry, acoustic-port clearance, and mechanical integration.
- Thermal performance and maximum component temperatures depend on workload, ambient conditions, airflow, enclosure design, and external loading.
- Connector insertion clearance and maximum component-height requirements should be verified for the final carrier or enclosure design.

### **9.4 Document Control** {.section-page}

| Field | Value |
|---|---|
| Product | UNIT PULSAR RP2350A |
| SKU | UE0103 |
| Product family | UNIT DevLab ecosystem |
| Hardware revision | V1.3.0 |
| Product Reference | Version 0.1.0 |
| Publication date | 2026-08-03 |

#### **9.5 Source Notes** {.section-page}

- The hardware V1.3.0 schematic title block contains the text `PULSAR RP230A` and revision `1.0.0`. This Product Reference uses the released product identification UNIT PULSAR RP2350A and hardware revision V1.3.0.

- The microSD hardware exposes a complete four-bit SDIO interface. Current UNIT Electronics Wiki examples use the SPI-compatible `CLK`, `CMD`, `DAT0`, and `DAT3` subset.

- `D8` and `D9` expose the RP2350A native USB D- and D+ signals through the board routing and must not be treated as conventional general-purpose digital I/O.

- `D13` / `BUILTIN1` is connected to GPIO22 on hardware V1.3.0.

### **9.6 Hardware Errata** {.section-page}

#### **SWD VCC and GND Silkscreen Labels**

On hardware revision V1.3.0, the `VCC` and `GND` silkscreen labels printed beside the SWD debug pads are reversed.

Use the following corrected electrical mapping when connecting an SWD debug probe:

| Printed silkscreen label | Actual electrical connection |
|---|---|
| `VCC` | `GND` |
| `GND` | `3.3 V` reference |

Verify the SWD pad connections before connecting a debug probe.

Following the incorrect silkscreen labels may reverse the probe power-reference and ground connections and may damage the board or debug equipment.

Refer to Section 4.8 for SWD connection guidance.
