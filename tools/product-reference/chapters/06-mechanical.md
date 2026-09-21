## **6 Mechanical Information**

Hardware revision V1.3.0 uses a narrow development-board form factor with two parallel castellated edge rows, four corner mounting holes, USB-C at one end, and the 22-pin HSTX FFC/FPC connector at the opposite end.

The board uses a 2.54 mm edge-pad pitch and a 15.24 mm spacing between the two castellated rows, providing a Nano-style mechanical layout.

### **6.1 Component-side Envelope** {.section-page}

![](hardware/resources/unit_top_v_1_3_0_pulsar_rp2350a.png){width=3.4in}

The component side contains the USB-C connector, pushbuttons, QWIIC connector, RP2350A, external memories, BMI270 IMU, ICS-41350 PDM microphone, power-management circuitry, and other onboard components.

Adequate vertical and lateral clearance should be provided around the USB-C connector, pushbuttons, QWIIC connector, and other top-side components. The castellated edge pads must remain accessible when the board is mounted on headers, carrier boards, sockets, or directly soldered to another PCB.

### **6.2 Bottom-side Envelope** {.section-page}

![](hardware/resources/unit_btm_v_1_3_0_pulsar_rp2350a.png){width=3.4in}

The bottom side provides access to the battery connector, microSD socket, HSTX FFC/FPC connector, configuration solder pads, SWD debug pads, and the microphone acoustic port.

Adequate clearance must be maintained for battery connection, microSD card insertion and removal, and FFC/FPC cable installation. Enclosures and carrier boards must not obstruct the microphone acoustic port.

### **6.3 Board Dimensions** {.section-page}

![](hardware/resources/unit_dimensions_v1_3_0_ue0103_pulsar_rp2350a.png){width=6.5in}

The principal mechanical dimensions of hardware revision V1.3.0 are summarized below.

| Parameter | Dimension |
|---|---:|
| Overall board length | 43.18 mm |
| Overall board width | 17.78 mm |
| Castellated-row spacing | 15.24 mm |
| Castellated-pad pitch | 2.54 mm |
| Mounting-hole diameter | Ø2.0 mm |
| Vertical mounting-hole spacing | 40.64 mm |

Four mounting holes are located near the corners of the PCB. The castellated edge connections follow a 2.54 mm pitch, with 15.24 mm spacing between the two parallel rows.

The dimensional drawing should be used as the primary reference for board-outline and mounting dimensions when designing carrier boards, fixtures, or enclosures.

### **6.4 Mechanical Integration Considerations** {.section-page}

When integrating the UNIT PULSAR RP2350A into a carrier board, fixture, or enclosure, provide sufficient clearance for:

- USB-C cable insertion and removal.
- QWIIC cable connection.
- Battery connector and cable routing.
- microSD card insertion and removal.
- HSTX FFC/FPC cable insertion and routing.
- BOOT and RESET button access.
- Castellated edge-pad soldering or header installation.
- SWD debug access when required.
- Configuration solder-pad access when required.
- The microphone acoustic port and its surrounding acoustic path.

PCB thickness, maximum top-side and bottom-side component heights, and connector insertion envelopes should be verified from the corresponding mechanical component specifications when they are critical to the final enclosure or carrier design.