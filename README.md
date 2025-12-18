# ArduinoPCPowerSwitch

Use an Arduino to simulate a momentary switch signal to a PC power header, allowing remote control of PC power on/off via a toggle switch.

## Overview

This project uses an Arduino to bridge a physical toggle switch with a PC's power button header. When you toggle the switch, the Arduino detects the state change and triggers a relay that simulates pressing the PC's power button, allowing you to remotely power your PC on or off.

**Use Case:** This was created to control the power switch of a MAME (Multiple Arcade Machine Emulator) arcade console built from a repurposed PC. The goal was to use an authentic SPST toggle switch like old-style arcade cabinets, but directly cutting power to the PC would risk drive corruption. This solution allows the switch to gracefully shut down the operating system through the power button mechanism before cutting power, eliminating the risk of data loss while maintaining the authentic arcade experience.

## How It Works

The sketch implements the following logic:

- **Detects Toggle Switch State**: Monitors a toggle switch connected to pin 2 with an internal pull-up resistor
- **Monitors PC Power State**: Reads the PC's USB 5V output on pin 12 to determine if the PC is currently on or off
- **Controls Relay**: Sends a momentary pulse signal (20ms) to pin 13 (connected to a 5V relay) to simulate pressing the power button
- **Smart Power Control**: 
  - When the switch is ON and PC is OFF → Triggers relay to power ON the PC
  - When the switch is OFF and PC is ON → Triggers relay to power OFF the PC
  - Includes a 5-second delay after sending the off signal to allow the PC time to shut down

## Hardware Requirements

- Arduino microcontroller (e.g., Arduino Uno)
- SPST (Single Pole Single Throw) toggle switch
- 5V relay module
- PC with ATX power header
- Jumper wires and breadboard (optional)

## Circuit Connections

- **Toggle Switch**: Connected between pin 2 and GND
- **Relay Signal**: Connected to pin 13
- **Relay Power**: Connected to 5V and GND
- **PC Detection**: USB 5V from PC connected to pin 12 (via voltage divider if needed)
- **PC Power Control**: Relay NO (Normally Open) contact connected to PC power switch header pins (simulating button press)

## Wiring Diagram

```
                          ┌─────────────────────┐
                          │      ARDUINO        │
                          │                     │
                   5V ────┤ 5V              GND ├──── GND
                          │                     │
        RELAY SIGNAL ──┬──┤ PIN 13        PIN 2 ├──┬── TOGGLE SWITCH
         (HIGH->pulse) │  │                     │  │
                       │  │              PIN 12 ├─┐│
                       │  └─────────────────────┘ ││
                       │                          ││
                       │                      PC USB 5V
                       │                       (to detect
                       │                        PC state)
                       │
                       │     ┌──────────────┐
                       └────>│   5V RELAY   │
                             │              │
                        ┌────┤ IN   SIGNAL  │
                        │    │              │
                        │    │   VCC   GND  ├──────┬──── GND
                        │    └─┬────┬───┬───┘      │
                        │      │    │   │          │
                        │     5V   GND  TOGGLE SW  │
                        │                          │
                        │     ┌─────────────────┐  │
                        │     │  RELAY NO/COM   │  │
                        │     │ (Normally Open) │  │
                        │     │                 │  │
                        └────>│ IN ────NO       │  │
                              │      |          │  │
                              │      +──────────┼──┘
                              │      |          │
                              │      COM        │
                              └──────┼──────────┘
                                     │
                        ┌────────────▼─────────────┐
                        │   PC ATX POWER HEADER    │
                        │                          │
                        │  ┌─ Ground (pin 24, 25)  │
                        │  │                       │
                        └──┼───────────────────────┘
                           │
                    (Simulates momentary press
                     of PC power button)
```

**Signal Flow:**

1. Toggle switch position is read by Arduino pin 2
2. PC power state is detected via USB 5V on pin 12
3. When switch state differs from PC state, Arduino pulses pin 13 HIGH for 20ms
4. This triggers the relay to close its NO contact momentarily
5. The closed relay contact simulates pressing the PC's power button

## Serial Output

The sketch outputs status information via serial at 9600 baud:

- Current switch position (on/off)
- Current PC state (on/off)
- Toggle actions and delays
