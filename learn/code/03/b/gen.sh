#!/bin/bash
TOP_DIR=../../../

cd $TOP_DIR || exit
rm hd10M.img
bximage -hd=10M -func=create -q hd10M.img
cd - || exit

nasm -I include/ mbr.S -o mbr.bin
nasm -I include/ loader.S -o loader.bin

dd if=./mbr.bin of=${TOP_DIR}/hd10M.img bs=512 count=1  conv=notrunc
dd if=./loader.bin of=${TOP_DIR}/hd10M.img bs=512 count=1 seek=2 conv=notrunc

rm mbr.bin
rm loader.bin