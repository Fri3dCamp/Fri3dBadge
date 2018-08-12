#!/bin/bash

ESPTOOL="./esptool"

$ESPTOOL \
    --chip esp32 \
    --port /dev/cu.SLAB_USBtoUART \
    --baud 921600 \
    --before default_reset \
    --after hard_reset \
    write_flash -z \
    --flash_mode dio \
    --flash_freq 80m \
    --flash_size detect \
    0xe000 ./boot_app0.bin \
    0x1000 ./bootloader_qio_80m.bin \
    0x10000 ./defaultFirmware.pde.bin \
    0x8000 ./defaultFirmware.pde.partitions.bin 
