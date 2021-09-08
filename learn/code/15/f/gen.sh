#!/bin/bash
TOP_DIR=../../..
BUILD_DIR=./build
IMG_NAME=hd10M.img

OBJDUMP=/usr/local/i386elfgcc/bin/i386-elf-objdump


if [ -e $TOP_DIR/$IMG_NAME ]; then
  rm -f ${TOP_DIR:?}/$IMG_NAME
fi


# for img
bximage -hd=10M -func=create -q $IMG_NAME
mv $IMG_NAME $TOP_DIR/$IMG_NAME

if ! make;
then
  exit 1
fi

$OBJDUMP -D $BUILD_DIR/kernel.bin > $BUILD_DIR/kernel.dump

cd ./command/
  ./complile.sh
cd - || exit 1

$OBJDUMP -D $BUILD_DIR/prog_arg > $BUILD_DIR/prog_arg.dump

pwd
# write img
dd if=$BUILD_DIR/mbr.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=1  conv=notrunc
dd if=$BUILD_DIR/loader.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=4 seek=2 conv=notrunc
dd if=$BUILD_DIR/kernel.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=200 seek=9 conv=notrunc

# shellcheck disable=SC2012
SEC_CNT=$(ls -l $BUILD_DIR/prog_arg |awk '{printf("%d", ($5+511)/512)}')
dd if=$BUILD_DIR/prog_arg of=${TOP_DIR}/$IMG_NAME bs=512 count="$SEC_CNT" seek=300 conv=notrunc
# shellcheck disable=SC2012
SEC_CNT=$(ls -l $BUILD_DIR/cat |awk '{printf("%d", ($5+511)/512)}')
dd if=$BUILD_DIR/cat of=${TOP_DIR}/$IMG_NAME bs=512 count="$SEC_CNT" seek=350 conv=notrunc
# shellcheck disable=SC2012
SEC_CNT=$(ls -l $BUILD_DIR/prog_pip |awk '{printf("%d", ($5+511)/512)}')
dd if=$BUILD_DIR/prog_pip of=${TOP_DIR}/$IMG_NAME bs=512 count="$SEC_CNT" seek=400 conv=notrunc

if [ "$1" == "" ]; then
  make clean
fi
