#!/bin/bash
TOP_DIR=../../..
BUILD_DIR=./build
IMG_NAME=hd10M.img

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

# write img
dd if=$BUILD_DIR/mbr.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=1  conv=notrunc
dd if=$BUILD_DIR/loader.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=4 seek=2 conv=notrunc
dd if=$BUILD_DIR/kernel.bin of=${TOP_DIR}/$IMG_NAME bs=512 count=200 seek=9 conv=notrunc

if [ "$1" == "" ]; then
  make clean
fi
