# RC Car Assembly Instructions

## Overview

This document provides the instructions for building your RC car. You'll need to 3D print the parts, assemble the components, and upload the code to the ESP32.

## 1. 3D Printing

Download the 3D print files from https://cults3d.com/en/3d-model/game/functional-rc-car-siege-drone.

## 2. Assembly

1. **Print the 3D printed parts**: Follow the provided print files and print the chassis, wheels, and other components.
2. **Attach the motors**: Attach the DC motors to the motor holes.
3. **Wiring**: Connect the motor driver, Arduino, and motors. Refer to the wiring diagram in Docs/wiring_diagram.md:
4. **Assemble the 3D printed parts**: Connect the wheels to the motor shafts, attach the top of the chassis (use tape or other form to secure top to bottom, with all components inside.

## 3. Uploading Code

1. Open the Arduino IDE.
2. Install the necessary libraries, Wifi.h, WebServer.h, TB6612_ESP32.h.
3. Install esp32 boards by Espressif Systems using the board manager in arduino IDE
4. Upload the code located in the src/esp_code.cpp directory to your ESP32.
5. Test the RC car after uploading the code, by typing your ESP32 IP adress into Google on a device connected to the same Wifi.

## Troubleshooting

- If the motors don't spin, check your wiring and ensure the motor driver is connected properly.
- If the car doesn't respond to the remote control, ensure the IP adress is correct, and your ssid and password are correct.
