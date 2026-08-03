## **9 Appendix**

### **9.1 Source Hierarchy**

1. V1.3 schematic, manufacturing BOM, and V1.3 board artwork for fitted
   components, visible labels, and board connections.
2. Official Raspberry Pi RP2350 datasheet for RP2350A component
   characteristics only.
3. Technical wiki for intended subsystem operation and firmware workflow.

### **9.2 Items Pending Validation**

- Correction of the schematic title block from `PULSAR RP230A / REV 1.0.0`
  to match the RP2350A V1.3 source package
- Module `VIN`, `VBAT`, USB, and 3.3 V rail electrical limits
- Power-source priority, battery charge current, and compatible battery cable
- Complete controlled HSTX and QWIIC connector pin-number/orientation drawings
- `D8` and `D9` edge-pad connectivity
- Board dimensions, mounting-hole coordinates, and mechanical keep-outs
- Validated clock rates, current consumption, and thermal behavior
- Reconciliation and test of all technical-wiki examples against V1.3 hardware
- Controlled pinout, topology, and dimensions artwork

### **9.3 Document Control**

| Field | Value |
|---|---|
| Product | UNIT DevLab PULSAR RP2350A |
| Manufacturer Part Number | UE0103 |
| Hardware artwork covered | V1.3.0 |
| Product Reference | 0.1.0, preview |
| Publication date | 2026-08-03 |
| Hardware status | Design complete; awaiting fabrication |
| Firmware status | Implementation documented in the wiki; results pending confirmation on manufactured units |

### **9.4 Source Inconsistencies**

- The V1.3 schematic filename, artwork, and BOM identify RP2350A, but the
  schematic title block says `PULSAR RP230A` and revision `1.0.0`.
- The supplied Product Reference DOCX describes an ESP32-H2 board and is not
  applicable to PULSAR RP2350A.
- Some wiki chapters describe SPI-oriented microSD examples, while the V1.3
  schematic shows a four-bit SDIO connection on GPIO2–GPIO7. This edition
  follows the schematic and leaves software behavior pending validation.
