#!/bin/bash


make TARGET=stm32f411
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/stm32f411/client.stm32f411 verify reset exit"