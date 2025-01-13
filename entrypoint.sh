#!/bin/bash

arduino-cli core install arduino:avr
arduino-cli lib install Braccio
arduino-cli lib install Ramp
arduino-cli lib install --git-url https://github.com/cgxeiji/CGx-InverseK.git
chmod a+rw /dev/ttyACM0
diff -u --color /root/Arduino/libraries/Braccio/src/Braccio.cpp /home/app/arduino_module/src/braccio_patch/Braccio_new.cpp > Braccio.diff
patch /root/Arduino/libraries/Braccio/src/Braccio.cpp -i Braccio.diff
diff -u --color /root/Arduino/libraries/Braccio/src/Braccio.h /home/app/arduino_module/src/braccio_patch/Braccio_new.h > Braccioh.diff
patch /root/Arduino/libraries/Braccio/src/Braccio.h -i Braccioh.diff
cp -r /root/Arduino /home/app
exec /wei-entrypoint.sh "$@"