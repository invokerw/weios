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

void init(void);

// 注意 main 函数要在第一位，链接的时候也需要确保 main.o 在第一位，否则要去修正 loader 中的 jump
int main(void) {
    put_str("I am kernel\n");
    init_all();

    while(1){
        mtime_sleep(1000);
    }
    return 0;
}

// init进程
void init(void) {
    uint32_t ret_pid = fork();
    if(ret_pid) {
        printf("i am father, my pid is %d, child pid is %d\n", getpid(), ret_pid);
    } else {  //子进程
        my_shell();
    }
    while(1);
}