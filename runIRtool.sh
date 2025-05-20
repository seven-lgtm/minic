#!/bin/sh
./commonclasstestcases/IRCompiler/Linux-aarch64/Ubuntu-22.04/IRCompiler -S -I -o ./tests/test1-1-1.ir tests/test1-1.c 
./commonclasstestcases/IRCompiler/Linux-aarch64/Ubuntu-22.04/IRCompiler  -R ./tests/test1-1-1.ir 
echo $?