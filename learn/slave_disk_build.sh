#!/bin/bash


IMG_NAME=hd50M_slave.img

bximage -hd=50M -func=create -q $IMG_NAME
#========================================================================
#                                bximage
#  Disk Image Creation / Conversion / Resize and Commit Tool for Bochs
#         $Id: bximage.cc 13481 2018-03-30 21:04:04Z vruppert $
#========================================================================
#
# Creating hard disk image 'hd50M_slave.img' with CHS=101/16/63 (sector size = 512)



# 1. write to bochs config
#   ata0-slave: type=disk, path="hd50M_slave.img", mode=flat, cylinders=101, heads=16, spt=63
# 2. 启动后运行 xp/b 0x475 查看硬盘数量
# 3. 分区 (下面都在 linux 下运行吧，mac 的 fdisk 命令使用方式不一样, 再研究)
#   1. fdisk -l $IMG_NAME # 查看分区内容 mac 使用 diskutil list $IMG_NAME or fdisk $IMG_NAME
#   2. fdisk $IMG_NAME # 开始分区
#     1. m 显示命令菜单
#     2. x 进入 extra function 菜单， m 显示子功能菜单, c 设置柱面数 101, h 磁头数 16(看上面 bximage 生成), r 返回上一级菜单
#     3. n 创建分区，p 创建主分区, 设置分区号，起始柱面(可以默认值)，结束柱面(自己设置)
#     4. n 创建分区，e 创建扩展分区，设置分区号，设置起始柱面，结束柱面
#     5. p 显示目前分区
#     6. n 创建分区，l 创建逻辑分区，设置柱面范围，划分一个或者若干个逻辑分区，占满空间即可
#     7. p 显示目前分区，l 查看已知文件系统 id
#     8. t 键设置分区 id，把逻辑分区的分区 id 设置为 0x66
#     9. p 显示目前分区，扩展分区中的逻辑分区 id 已经变成了 0x66
#    10. w 写入退出
#   3. fdisk -l $IMG_NAME # 查看分区内容 mac 使用 diskutil list $IMG_NAME or fdisk $IMG_NAME