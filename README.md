# Installation

## Arduino Library for the Fri3d Camp badge

Download this repo as a .ZIP file and install it, similar to other Arduino libraries: https://www.arduino.cc/en/Guide/Libraries#toc4

## ESP32 Board for the Fri3d Camp badge

Download the repo from https://github.com/espressif/arduino-esp32 as a .ZIP file and unzip it to an espressif/esp32 directory in your Arduino sketchbook.
Windows users can run get.exe, found in the “esp32/tools” folder.
!! Run this as an administrator !!


Mac and Linux users should run the tools/get.py python script to download the tools. Using a terminal, navigate to the esp32/tools folder. Then type: "python get.py"

The “get.py” python script will download the Xtensa GNU tools and the ESP32 software development kit (SDK), and unzip them to the proper location. You should see a few new folders in the “tools” directory, including “sdk” and “xtensa-esp32-elf” once it’s done.

## Usage

Explore the examples for sample Arduino code for the Fri3d Camp badge unnder `File > Examples > Fri3dBadge`

## Libraries

* `Fri3dMatrix` supports the LED matrices with `putPixel`, `getPixel` and `render` functions. See the `matrix` example for a basic setup.
