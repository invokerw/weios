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