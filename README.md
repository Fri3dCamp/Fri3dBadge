# Installation

## Arduino Library for the Fri3d Camp badge

Download this repo as a .ZIP file and install it, similar to other Arduino libraries: https://www.arduino.cc/en/Guide/Libraries#toc4

## ESP32 Board for the Fri3d Camp badge

### Windows users

Download the repo from https://github.com/espressif/arduino-esp32 as a .ZIP file and unzip it to an `espressif/esp32` directory in your `Mydocuments\Arduino\hardware` folder.

Run `get.exe` (make sure to run this as administrator), found in the `esp32/tools` folder.

### Mac and Linux users

Download the repo from https://github.com/espressif/arduino-esp32 as a .ZIP file and unzip it to an `espressif/esp32` directory in your Home directory.

Run the `tools/get.py` python script to download the tools. Using a terminal, navigate to the `esp32/tools` folder and run `python get.py`.

The `get.py` python script will download the Xtensa GNU tools and the ESP32 software development kit (SDK), and unzip them to the proper location. You should see a few new folders in the `tools` directory, including `sdk` and `xtensa-esp32-elf` once it’s done.

## Usage

When the ESP32 board and this library have been installed, the ESP boards (under `Tools/Board`) and Fri3d Camp Badge examples (under `File/Examples`) should be available in your Arduino IDE.

In order to flash code to your badge:

* Connect the badge to your computer with a USB cable
* Select the `ESP32 Dev Module` board under `Tools/Board` 
* Set your port to the correct port under `Tools/Port`. On a modern MacBook Pro, this port is `/dev/cu.SLAB_USBtoUART`.
* You can now upload Arduino programs to the Fri3d Camp badge.
* Explore the examples for sample Arduino code for the Fri3d Camp badge unnder `File > Examples > Fri3dBadge`

### Library support

This library offers various classes to easily interface with the peripherals on board the Fri3d Camp badge. The following classes are available:

* `Fri3dAccelerator` supports the ADXL345 accelerometer, using Adafruit's Sensor classes. The `1.Basics/accelerometer` demonstrates its usage.
* `Fri3dButtons` supports the two buttons and two touchpads with `getButton` and `getTouchpad` functions. The `1.Basics/buttons` example shows how to check the button and touchpad states.
* `Fri3dBuzzer` supports the buzzer with `setFrequency` (0-1000s) and `setVolume` (0-255) functions. Check `1.Basics/buzzer` for example code.
* `Fri3dMatrix` supports the LED matrices with `setPixel` and `getPixel` functions on a 14x5 screen buffer. The matrix runs a thread in the background to render the LED matrix. See the `1.Basics/matrix` example for a basic setup and the `1.Basics/font` example for a scrolling text demo.
* `Fri3dServoJewel` supports servo motors, using the Servo Jewel add-on board that comes with the Fri3d Camp robot kit. Check `3.Jewels/OneServo` and `3.Jewels/TwoServos` examples for demos.

# Problems & solutions

### Uploading the badge does not work
* Make sure the battery is switched off. If this does not work unplug the badge from your pc and plug it back in. Now it should work.
