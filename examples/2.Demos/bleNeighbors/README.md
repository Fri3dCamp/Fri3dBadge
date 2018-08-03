Beacon BLE badge
================

This code creates a Bluetooth Low Energy (BLE) Beacon named "friedAABBCCDDEEFF", and scans for other badges that are similarly named "friedXXXXXXXXX", and displays the number of them on the LED screen.

Screenshot
==========

![Fri3dcamp badge displaying the number of neighbooring badges](fri3dcamp-esp12-badge-beacon_600x.jpg)

TODO
====

* Lower the TX power, beacon is visible up to 50m
* Display something useful instead of "0" on the left screen
* Add a webinterface to enter a nickname, and then display them on the screen

Serial console
==============

```
ets Jun  8 2016 00:22:57
rst:0x10 (RTCWDT_RTC_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0018,len:4
load:0x3fff001c,len:808
load:0x40078000,len:6084
load:0x40080000,len:6696
entry 0x400802e4
===== Setup the Beacon... =====
My beacon name is: fried230951460
Beacon operational! You should be able to see it on your Beacon scanner, for example on your phone!
===== Scanning... =====
Advertised Device: Name: , Address: 24:4b:03:7e:8f:d4, manufacturer data: 7500420401808e244b037e8fd4fe8f9025fc5701000000000000 
Advertised Device: Name: fried1941720, Address: d8:a0:1d:00:07:4a, txPower: -21 
===== Number of badges: ===== 
1
===== Scanning... =====
Advertised Device: Name: , Address: 24:4b:03:7e:8f:d4, manufacturer data: 7500420401808e244b037e8fd4fe8f9025fc5701000000000000 
Advertised Device: Name: fried1941720, Address: d8:a0:1d:00:07:4a, txPower: -21 
===== Number of badges: ===== 
1

[...]

```
