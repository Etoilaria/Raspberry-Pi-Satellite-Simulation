# Raspberry-Pi-Satellite-Simulation

#### An embedded systems project that tracks the health of a simulated satellite and displays it using a Raspberry Pi circuit ####

The project is written in C and uses Raspberry Pi GPIO for the button and LEDs.

The program will cycle through three predefined telemetry datasets using a push button. Each set will be compared against healthy satellite ranges and be displayed by the circuit as the following:

- Healthy: Long green LED flashes
- Warning: 5 Rapid red LED flashes then green LED flashes
- Unhealthy: Long red LED flashes

### Hardware Components

- Raspberry Pi
-  Push button
-  Green and red LEDs
-  Breadboard
-  Resistors
-  Jumper wires

### Status

In progress!
