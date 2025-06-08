#!/bin/sh
./IRCompiler -S -I -o ./tests/test1-1-1.ir tests/test1-1.c 
./IRCompiler  -R ./tests/test1-1-1.ir 
echo $?