## **6 Mechanical Information**

Hardware revision V1.3.0 uses a narrow development-board layout with two parallel
edge-pad rows, four corner mounting holes, USB-C at one end, and the 22-pin HSTX
connector at the opposite end.

### **6.1 Component-side Envelope** {.section-page}

![](hardware/resources/unit_top_v_1_3_0_pulsar_rp2350a.png){width=3.4in}

USB-C, pushbuttons, QWIIC, and the tallest top-side components require vertical
and tool-access clearance. Edge castellations/pads must remain accessible for
headers, carrier sockets, or direct soldering.

### **6.2 Bottom-side Envelope** {.section-page}

![](hardware/resources/unit_btm_v_1_3_0_pulsar_rp2350a.png){width=3.4in}

The battery connector, microSD socket, microphone, and HSTX connector require
bottom-side clearance. An enclosure must not obstruct the microphone acoustic
port or prevent card and flex-cable insertion.

### **6.3 Mechanical Data Not Specified** {.section-page}

A controlled board-outline drawing, PCB thickness, mounting-hole coordinates,
keep-outs, connector insertion envelopes, and component height table are not
present in the supplied package. Do not derive production dimensions from the
rendered images.

An enclosure or carrier design requires independently controlled values for:

- overall board length, width, and thickness;
- edge-row pitch and row spacing;
- mounting-hole diameter and coordinates;
- USB-C, QWIIC, battery, microSD, and HSTX access envelopes;
- top/bottom maximum component height;
- microphone acoustic keep-out; and
- insertion/removal paths for card, battery plug, and FFC/FPC cable.
