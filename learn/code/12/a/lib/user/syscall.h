#ifndef __LIB_USER_SYSCALL_H__
#define __LIB_USER_SYSCALL_H__
#include "stdint.h"
enum SYSCALL_NR {
    SYS_GETPID,
    SYS_WRITE
};
uint32_t getpid(void);
uint32_t write(char* str);
#endif // __LIB_USER_SYSCALL_H__