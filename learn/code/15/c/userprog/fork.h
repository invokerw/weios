#ifndef __USERPROG_FORK_H__
#define __USERPROG_FORK_H__
#include "thread.h"
// fork 子进程, 只能由用户进程通过系统调用 fork 调用,
// 内核线程不可直接调用, 原因是要从 0 级栈中获得 esp3 等
pid_t sys_fork(void);
#endif // __USERPROG_FORK_H__