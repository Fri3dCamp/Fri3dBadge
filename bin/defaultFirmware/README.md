# Flashing default Firmware using ESPtool

Instead of using the Arduino IDE to flash the badge, also the ESPtool can be used.
Starting from compiled binarie files, this is faster

## flash.sh

When using Linux.

## flash.bat

When usinh Windows.
Edit the file to locate correct location of ESPtool (if not found) and/or add to PATH environment variable.

When no argument provided, the last COM port will be selected. When argument provided, will be flashed to to the specified COm port.

TODO: ask user which COM port to use and add vendor detection.

## flash.py

For automatically flashing multiple badges at a time, without user interaction.
The scripts constantly scan for new serial ports and when one detected with correct vendor ID, 
the script will start trying to flash the firmware.
Using Python. Currently optimized for Windows, should be easily adapteable.

TODO: 
* More logging
* Linux and Mac compatible