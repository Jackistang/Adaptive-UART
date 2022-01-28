#!/bin/bash

cmake --build build

if [ $? -eq 0 ];
then
    /home/tangjia/Jackistang/rp2040_mouse/tools/openocd/src/openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -s /home/tangjia/Jackistang/rp2040_mouse/tools/openocd/tcl -c "program $1 verify reset exit"
fi
