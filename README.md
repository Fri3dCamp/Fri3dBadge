# Arduino Library for the Fri3d Camp Badge

This library offers simple interfaces to the hardware peripherals on the Fri3d Camp Badge so you can program the badge using the Arduino IDE and related programming environments. You can find more information on the badge at http://fri3d.be/badge

## Installation

Installation is two-fold, first of all you need to install support for the Fri3d Badge. The badge carries an ESP32, so we need to install support for the ESP32 boards.

The second step is to install the arduino library holding all the utility functions etc for the Fri3dBadge.

### Arduino IDE
The arduino-esp32 project released support for installing the ESP directly from the boardsmanager of the arduino IDE. You can find detailed instructions at https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

This should work for windows, linux and mac users.

Possibly when compiling, you get BLE and ESP32_AzureIoT_Arduino error. This can be fixed by installing these manually.
Libraries can be downloaded from (as defined on https://github.com/espressif/arduino-esp32/tree/master/libraries):
* https://github.com/VSChina/ESP32_AzureIoT_Arduino/archive/67dfa4f31ef88b0938dd87d955612100dea5562e.zip
* https://github.com/nkolban/ESP32_BLE_Arduino/archive/7951347ed68313d75c367e1f2cce763cb56d1eb2.zip
These should be put in the respective folders under \Arduino15\packages\Espressif\hardware\esp32\1.0.1\libraries

### Arduino Library for the Fri3d Camp badge
Download this repo as a .ZIP file and install it, similar to other Arduino libraries: https://www.arduino.cc/en/Guide/Libraries#toc4

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

## Problems & solutions

### Uploading the badge does not work
* Make sure the battery is switched off. If this does not work unplug the badge from your pc and plug it back in. Now it should work.

### I get errors concerning multiple wifi stacks
* Make sure you have the latest version of arduino IDE installed, most of the development was done using version 1.8.5

## Default firmware
See `bin` folder.
