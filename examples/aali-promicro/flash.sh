#!/bin/bash

make TARGET=nrf52840 BOARD=dongle __FLASH=0x26000 __FLASH_SIZE=0xda000

arm-none-eabi-objcopy -O ihex build/nrf52840/dongle/main.nrf52840 main.hex


python3 tools/uf2conv.py main.hex -f 0xADA52840 -o flash.uf2
