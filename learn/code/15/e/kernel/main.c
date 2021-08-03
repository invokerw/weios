#include "print.h"
#include "init.h"
#include "debug.h"
#include "memory.h"
#include "thread.h"
#include "interrupt.h"
#include "console.h"
#include "process.h"
#include "stdio_kernel.h"
#include "syscall_init.h"
#include "syscall.h"
#include "stdio.h"
#include "timer.h"
#include "fs.h"
#include "dir.h"
#include "string.h"
#include "syscall.h"
#include "shell.h"
#include "assert.h"

void init(void);

// 注意 main 函数要在第一位，链接的时候也需要确保 main.o 在第一位，否则要去修正 loader 中的 jump
int main(void) {
    put_str("I am kernel\n");
    init_all();

    // 写入应用程序
    {
        int32_t fd = sys_open("/prog_arg", O_RDWR);
        if(fd != -1) {
            sys_close(fd);
            sys_unlink("/prog_arg");
        }
        uint32_t file_size = 5000;
        uint32_t sec_cnt = DIV_ROUND_UP(file_size, 512);
        struct disk* sda = &channels[0].devices[0];
        void* prog_buf = sys_malloc(file_size);
        ide_read(sda, 300, prog_buf, sec_cnt);
        fd = sys_open("/prog_arg", O_CREAT|O_RDWR);
        if (fd != -1) {
            if(sys_write(fd, prog_buf, file_size) == -1) {
                printk("file write error!\n");
                while(1);
            }
        }
    }
    {
        int32_t fd = sys_open("/cat", O_RDWR);
        if(fd != -1) {
            sys_close(fd);
            sys_unlink("/cat");
        }
        uint32_t file_size = 5500;
        uint32_t sec_cnt = DIV_ROUND_UP(file_size, 512);
        struct disk* sda = &channels[0].devices[0];
        void* prog_buf = sys_malloc(file_size);
        ide_read(sda, 350, prog_buf, sec_cnt);
        fd = sys_open("/cat", O_CREAT|O_RDWR);
        if (fd != -1) {
            if(sys_write(fd, prog_buf, file_size) == -1) {
                printk("file write error!\n");
                while(1);
            }
        }
    }



    cls_screen();
    console_put_str("[wei@weios /]$ ");
    while(1){
        mtime_sleep(1000);
    }
    return 0;
}

// init 进程
void init(void) {
    uint32_t ret_pid = fork();
    if(ret_pid) {  // 父进程
        while(1);
    } else {	  // 子进程
        my_shell();
    }
    panic("init: should not be here");
}