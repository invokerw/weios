BUILD_DIR = ./build
DISK_IMG = hd10M.img
ENTRY_POINT = 0xc0001500
AS = nasm
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

EXES = kernel.bin mbr.bin loader.bin

INCLUDE = -I lib/ -I lib/kernel/ -I lib/user/ -I kernel/ -I device/ -I thread/ -I userprog/
VPATH = boot:device:kernel:lib:lib/kernel:lib/user:thread:userprog

# 确保 main.o 在 链接的第一位，否则就要修改 loader 中的跳转
KERNEL_C_OBJS = main.o init.o interrupt.o timer.o debug.o string.o bitmap.o \
	memory.o thread.o list.o sync.o console.o keyboard.o ioqueue.o syscall.o syscall_init.o \
	stdio_kernel.o ide.o
KERNEL_AS_OBJS = kernel.o print.o switch.o tss.o process.o stdio.o

vpath %.c $(VPATH)
vpath %.S $(VPATH)
KERNEL_C_OBJ_WITH_DIR = $(addprefix $(BUILD_DIR)/,$(KERNEL_C_OBJS))
KERNEL_AS_OBJ_WITH_DIR = $(addprefix $(BUILD_DIR)/,$(KERNEL_AS_OBJS))

all:  mk_dir $(addprefix $(BUILD_DIR)/, $(EXES))


AS_FLAGS = -f elf
AS_LIB = -I boot/include/

CFLAGS = -m32 -Wall $(INCLUDE) -c -fno-builtin -W -Wstrict-prototypes \
         -Wmissing-prototypes -fno-stack-protector
LDFLAGS = -melf_i386 -Ttext $(ENTRY_POINT) -e main -Map $(BUILD_DIR)/kernel.map

mk_dir:
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR);fi

$(BUILD_DIR)/mbr.bin: boot/mbr.S
	$(AS) $(AS_LIB) $< -o $@

$(BUILD_DIR)/loader.bin: boot/loader.S
	$(AS) $(AS_LIB) $< -o $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/kernel.bin: $(KERNEL_C_OBJ_WITH_DIR) $(KERNEL_AS_OBJ_WITH_DIR)
	$(LD) $(LDFLAGS) $^ -o $@

.PHONY : clean

clean:
	rm -rf $(BUILD_DIR)

