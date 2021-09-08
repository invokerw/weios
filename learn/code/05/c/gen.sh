#!/bin/bash
TOP_DIR=../../../
IMG_NAME=hd10M.img

cd $TOP_DIR || exit
rm $IMG_NAME
bximage -hd=10M -func=create -q $IMG_NAME
cd - || exit

cd boot || exit
nasm -I include/ mbr.S -o mbr.bin

nasm -I include/ loader.S -o loader.bin

dd if=./mbr.bin of=${TOP_DIR}/../$IMG_NAME bs=512 count=1  conv=notrunc
dd if=./loader.bin of=${TOP_DIR}/..//$IMG_NAME bs=512 count=4 seek=2 conv=notrunc

rm mbr.bin
rm loader.bin
cd - || exit

cd kernel || exit
# /usr/local/i386elfgcc/bin/i386-elf-gcc -S main.s main.c
# /usr/local/i386elfgcc/bin/i386-elf-readelf -e kernel.bin
/usr/local/i386elfgcc/bin/i386-elf-gcc -c -o main.o main.c
[[ ! $? ]] && exit 1

/usr/local/i386elfgcc/bin/i386-elf-ld main.o -Ttext 0xc0001500 -e main -o kernel.bin
[[ ! $? ]] && exit 1

dd if=kernel.bin of=${TOP_DIR}/../$IMG_NAME bs=512 count=200 seek=9 conv=notrunc
rm main.o
rm kernel.bin
cd - || exit
