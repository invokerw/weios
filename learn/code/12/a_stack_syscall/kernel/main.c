#include "print.h"
#include "init.h"
#include "debug.h"
#include "memory.h"
#include "thread.h"
#include "interrupt.h"
#include "console.h"
#include "process.h"
#include "syscall_init.h"
#include "syscall.h"
#include "stdio.h"

static void k_thread_a(void*);
static void k_thread_b(void*);
static void u_prog_a(void);
static void u_prog_b(void);


// 注意 main 函数要在第一位，链接的时候也需要确保 main.o 在第一位，否则要去修正 loader 中的 jump
int main(void)  {
    put_str("I am kernel\n");
    put_str("wei fei\n");
    init_all();

    process_execute(u_prog_a, "user_prog_a");
    process_execute(u_prog_b, "user_prog_b");

    intr_enable();
    console_put_str(" main_pid:0x");
    console_put_int(sys_getpid());
    console_put_char('\n');
    thread_start("k_thread_a", 31, k_thread_a, "argA ");
    thread_start("k_thread_b", 31, k_thread_b, "argB ");

    while(1);
}

void k_thread_a(void* ) {
    console_put_str(" thread_a_pid:0x");
    console_put_int(sys_getpid());
    console_put_char('\n');
    while(1);
}

void k_thread_b(void* ) {
    console_put_str(" thread_b_pid:0x");
    console_put_int(sys_getpid());
    console_put_char('\n');
    while(1);
}

void u_prog_a(void) {
    char* name = "prog_a";
    printf(" I am %s, my pid:%d%c", name, getpid(),'\n');
    while(1);
}

void u_prog_b(void) {
    char* name = "prog_b";
    printf(" I am %s, my pid:%d%c", name, getpid(),'\n');
    while(1);
}