#!/bin/bash
arduino-cli core install arduino:avr
arduino-cli compile --fqbn arduino:avr:uno /home/app/arduino_module/src/src.ino
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno /home/app/arduino_module/src/src.ino