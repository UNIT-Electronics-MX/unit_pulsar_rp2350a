## **9 Appendix**

### **9.1 Schematic**

The following three sheets are rendered from
`unit_sch_v_1_3_0_pulsar_rp2350a.pdf`. The PDF remains the authoritative
electrical drawing. The title block still contains `PULSAR RP230A` and revision
`1.0.0`; this is a known document-control inconsistency in the supplied V1.3
package and does not change the fitted RP2350A identified by the BOM and
artwork.

<div class="schematic-page">

#### **9.1.1 Processor, Memory, USB, I/O, and Power Entry**

![](hardware/resources/unit_schematic_v_1_3_0_pulsar_rp2350a_sheet_1.png){width=7.2in}

</div>

<div class="schematic-page">

#### **9.1.2 microSD, BMI270, HSTX Connector, and PDM Microphone**

![](hardware/resources/unit_schematic_v_1_3_0_pulsar_rp2350a_sheet_2.png){width=7.2in}

</div>

<div class="schematic-page">

#### **9.1.3 3.3 V Regulator**

![](hardware/resources/unit_schematic_v_1_3_0_pulsar_rp2350a_sheet_3.png){width=7.2in}

</div>

### **9.2 Source Hierarchy**

1. V1.3 schematic, manufacturing BOM, and V1.3 board artwork define fitted
   components, visible labels, and board connectivity.
2. The official Raspberry Pi RP2350 datasheet defines RP2350A component
   capabilities and limits.
3. The technical wiki defines intended subsystem operation and firmware
   workflow.
4. The compile-checked C++ example collection reconciles wiki code with the
   installed UNIT RP2350 core APIs.

### **9.3 Values Not Specified by the Source Package** {.section-page}

- A schematic title block matching UNIT PULSAR RP2350 V1.3.0
- Module `VIN`, `VBAT`, USB, and 3.3 V rail electrical limits
- Power-source priority, charge current, and approved battery assembly
- Complete numbered HSTX and QWIIC connector drawings
- `D8` and `D9` edge-pad disposition
- Board dimensions, mounting coordinates, and mechanical keep-outs
- Current consumption, thermal behavior, and validated interface rates
- Module-level runtime performance for the wiki and C++ examples
- Final controlled pinout, topology, and dimensions artwork

### **9.4 Document Control** {.section-page}

| Field | Value |
|---|---|
| Product | UNIT PULSAR RP2350 |
| Product family | UNIT DevLab ecosystem |
| Manufacturer Part Number | UE0103 |
| Hardware artwork | V1.3.0 |
| Product Reference | Version 0.1.0 |
| Publication date | 2026-08-03 |
| Firmware | 28 compile-checked examples |

### **9.5 Source Inconsistencies** {.section-page}

- The V1.3 schematic filename, artwork, and BOM identify RP2350A, but the
  schematic title block says `PULSAR RP230A` and revision `1.0.0`.
- The supplied legacy Product Reference DOCX describes an ESP32-H2 board and is
  not applicable to UNIT PULSAR RP2350.
- Wiki microSD examples use SPI mode, while the V1.3 schematic exposes a full
  four-bit SDIO group. Both are represented correctly: SPI uses the compatible
  CLK/CMD/DAT0/DAT3 subset.
- The wiki's original Blink definition used GPIO22, while the V1.3 schematic
  connects `D13` / `BUILTIN1` to GPIO20. Repository examples follow GPIO20.
