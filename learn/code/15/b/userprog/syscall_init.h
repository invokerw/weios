#ifndef __USERPROG_SYSCALL_INIT_H__
#define __USERPROG_SYSCALL_INIT_H__
#include "stdint.h"
void syscall_init(void);
uint32_t sys_getpid(void);
void sys_putchar(uint8_t char_asci);
#endif  //__USERPROG_SYSCALL_INIT_H__