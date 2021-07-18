#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    if len(sys.argv) != 2 and len(sys.argv) != 4:
        print("eg:")
        print("    "+sys.argv[0] + " 0x1234")
        print("    "+sys.argv[0] + " pde pte offset")

    if len(sys.argv) == 2:
        data = int(sys.argv[1], 16)
        pde = (data & 0xffc00000) >> 22
        pte = (data & 0x003ff000) >> 12
        offset = (data & 0x00000fff)
        print("pde:{"+str(pde)+"}, pte:{"+str(pte)+"}, offset={"+str(offset)+"}")
    elif len(sys.argv) == 4:
        pde = int(sys.argv[1], 10)
        pte = int(sys.argv[2], 10)
        offset = int(sys.argv[3], 10)
        data = ((pde << 22) & 0xffc00000) | ((pte << 12) & 0x003ff000) | (offset & 0x00000fff)
        print(hex(data))


