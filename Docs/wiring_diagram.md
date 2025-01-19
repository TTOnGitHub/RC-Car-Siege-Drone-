# Components:
- ESP32
- TB6612FNG Motor Driver
- 6 Pre-resisted LEDs
- 9V Battery
- Breadboard
- N20 Micro Geared Motor x2 6v

# Connections:

## TB6612FNG to Motors

- Motor 1 → A01 and A02
- Motor 2 → B01 and B02

## TB6612FNG to ESP32 (Motor Driver Control Pins):

- ESP32 Pin D13 → TB6612FNG Pin AIN1
- ESP32 Pin D12 → TB6612FNG Pin BIN1
- ESP32 Pin D14 → TB6612FNG Pin AIN2
- ESP32 Pin D27 → TB6612FNG Pin BIN2
- ESP32 Pin D26 → TB6612FNG Pin PWMA
- ESP32 Pin D25 → TB6612FNG Pin PWMB
- ESP32 Pin D33 → TB6612FNG Pin STBY

## Power Supply:

- 9V Battery positive (+) → ESP32 VIN pin
- 9V Battery positive (+) → TB6612FNG VM pin
- 9V Battery negative (-) → ESP32 GND pin
- 9V Battery negative (-) → TB6612FNG GND pin

## LEDs:

- Connect ESP32 3.3V pin to the positive side of a breadboard rail.
- Connect ESP32 GND pin to the negative side of breadboard rail.
- Connect each positive wire of the LEDs in series to the positive side of breadboard rail.
- Connect each negative wire of the LEDs to the negative side of breadboard rail.
