#!/bin/sh
arm-linux-gnueabihf-gcc -S -o tests/test1-1-1.s tests/test1-1.c
arm-linux-gnueabihf-gcc -static -g -o tests/test1-1-1 tests/test1-1-1.s
qemu-arm-static tests/test1-1-1
echo $?