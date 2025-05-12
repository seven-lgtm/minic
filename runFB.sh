#!/bin/sh
./build/minic -S -I -o tests/test1-1.ir tests/test1-1.c
./build/minic -S -o tests/test1-1.s tests/test1-1.c
arm-linux-gnueabihf-gcc -static -g -o tests/test1-1 tests/test1-1.s
qemu-arm-static tests/test1-1
echo $?