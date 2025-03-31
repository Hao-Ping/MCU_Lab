#!/bin/bash
cd "$(dirname "$BASH_SOURCE")"

avr-gcc -std=c99 -g -Os -Wall -mcall-prologues -fno-exceptions -mmcu=atmega328p -o main.obj main.c
avr-objcopy -R .eeprom -O ihex main.obj main.hex
avrdude -c stk500v1 -P /dev/cu.usbmodem140111 -b 19200 -p m328p -U flash:w:main.hex
