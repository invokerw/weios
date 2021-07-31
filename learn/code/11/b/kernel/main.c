#include "print.h"
#include "init.h"
#include "debug.h"
#include "memory.h"
#include "thread.h"
#include "interrupt.h"
#include "console.h"
#include "process.h"

static void k_thread_a(void*);
static void k_thread_b(void*);
static void u_prog_a(void);
static void u_prog_b(void);
int test_var_a = 0;
int test_var_b = 0;

// 注意 main 函数要在第一位，链接的时候也需要确保 main.o 在第一位，否则要去修正 loader 中的 jump
int main(void)  {
    put_str("I am kernel\n");
    put_str("wei fei\n");
    init_all();

    thread_start("k_thread_a", 31, k_thread_a, "argA ");
    thread_start("k_thread_b", 31, k_thread_b, "argB ");
    process_execute(u_prog_a, "user_prog_a");
    process_execute(u_prog_b, "user_prog_b");

    intr_enable(); // 打开中断,使时钟中断起作用

    while(1);
}

void k_thread_a(void* ) {
    while(1) {
        console_put_str(" v_a:0x");
        console_put_int(test_var_a);
    }
}

void k_thread_b(void* ) {
    while(1) {
        console_put_str(" v_b:0x");
        console_put_int(test_var_b);
    }
}

void u_prog_a(void) {
    while(1) {
        test_var_a++;
    }
}

void u_prog_b(void) {
    while(1) {
        test_var_b++;
    }
}