#!/bin/bash
TOP_DIR=../../../

cd $TOP_DIR || exit
rm hd10M.img
bximage -hd=10M -mode=create -q hd10M.img
cd - || exit

nasm mbr.S -o mbr.bin
dd if=./mbr.bin of=${TOP_DIR}/hd10M.img bs=512 count=1  conv=notrunc
rm mbr.bin