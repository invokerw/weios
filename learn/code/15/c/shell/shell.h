#ifndef __KERNEL_SHELL_H__
#define __KERNEL_SHELL_H__
#include "fs.h"
void print_prompt(void);
void my_shell(void);
extern char final_path[MAX_PATH_LEN];
#endif // __KERNEL_SHELL_H__