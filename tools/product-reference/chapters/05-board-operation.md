## **5 Pre-production Operation Notes**

The technical wiki documents the intended firmware workflow and subsystem
operation. Those examples are not reproduced in this Product Reference; their
results will be confirmed on the first manufactured units. The complete
sketches are maintained under `software/cpp_examples/`.

For initial bench work:

1. Inspect the board and confirm its artwork revision.
2. Review the V1.3 schematic and the pending electrical limits in Section 2.
3. Power through USB-C for first inspection; do not connect a battery or an
   external `VIN` source until its limits and polarity have been validated.
4. Establish a common ground before attaching test equipment or peripherals.
5. Validate the user LED and serial upload path before enabling external
   memory, storage, sensors, audio, or HSTX output.
6. Confirm each peripheral mapping against Section 4 and observe the signals
   with suitable test equipment before relying on captured data.

Host framework aliases, GPIO initialization, PSRAM setup, SDIO support, and
HSTX library behavior depend on the selected board package. The wiki is an
implementation work-in-progress and may contain mappings that predate the V1.3
schematic review.

### **5.1 Current Wiki Coverage**

- Board setup and LED validation
- ADC and WS2812 examples
- Internal and external I2C examples
- microSD experiments
- HSTX display experiments
- PSRAM allocation examples
- PDM microphone capture
- A combined demonstration application

Results, performance claims, and troubleshooting instructions from these
chapters remain pending confirmation on manufactured hardware.
