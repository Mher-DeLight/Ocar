#!/bin/bash
cmake -B build
cmake --build build
./build/Ocar main.ocar
nasm -f elf64 out.asm -o out.o
ld out.o -o out
echo "== PROGRAM START =="
./out
echo "== PROGRAM END =="