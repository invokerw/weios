#!/bin/bash
TOP_DIR=../../..
IMG_NAME=hd10M.img
BUILD_DIR=./build
GCC=/usr/local/i386elfgcc/bin/i386-elf-gcc
LD=/usr/local/i386elfgcc/bin/i386-elf-ld


if [ -e $TOP_DIR/$IMG_NAME ]; then
  rm -f ${TOP_DIR:?}/$IMG_NAME
fi

if [ ! -d "$BUILD_DIR/boot" ];then
    mkdir -p $BUILD_DIR/boot
fi
if [ ! -d "$BUILD_DIR/kernel" ];then
    mkdir -p $BUILD_DIR/kernel
fi

# for img
bximage -hd=10M -mode=create -q $IMG_NAME
mv $IMG_NAME $TOP_DIR/$IMG_NAME

# for boot
nasm -I ./boot/include/ -o $BUILD_DIR/boot/mbr.bin ./boot/mbr.S
nasm -I ./boot/include/ -o $BUILD_DIR/boot/loader.bin ./boot/loader.S

# for kernel
nasm -f elf -o $BUILD_DIR/kernel/print.o lib/kernel/print.S
nasm -f elf -o $BUILD_DIR/kernel/kernel.o kernel/kernel.S
$GCC -m32 -I lib/kernel/ -I lib/  -c -o $BUILD_DIR/kernel/init.o kernel/init.c
$GCC -m32 -I lib/kernel/ -I lib/  -c -o $BUILD_DIR/kernel/interrupt.o kernel/interrupt.c
$GCC -m32 -I lib/kernel/ -I lib/  -c -o $BUILD_DIR/kernel/main.o kernel/main.c
# 这里设置了 0xc0001500 为起始虚拟地址，loader 也跳转到了 0xc0001500，所以 0xc0001500 必须是 main 函数的起始位置，
# 因此链接的时候需要把 main.o 放在最前面, 除非可以自己做到重定位到 main。使用 objdump 可以查看
$LD -melf_i386 -Ttext 0xc0001500 -e main -o $BUILD_DIR/kernel/kernel.bin $BUILD_DIR/kernel/main.o \
  $BUILD_DIR/kernel/init.o $BUILD_DIR/kernel/interrupt.o  $BUILD_DIR/kernel/kernel.o $BUILD_DIR/kernel/print.o

# write img
dd if=$BUILD_DIR/boot/mbr.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=1  conv=notrunc
dd if=$BUILD_DIR/boot/loader.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=4 seek=2 conv=notrunc
dd if=$BUILD_DIR/kernel/kernel.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=200 seek=9 conv=notrunc

if [ "$1" == "" ]; then
  rm -rf $BUILD_DIR
fi
