#ifndef __DEVICE_CONSOLE_H__
#define __DEVICE_CONSOLE_H__
#include "stdint.h"
void console_init(void);
void console_acquire(void);
void console_release(void);
void console_put_str(char* str);
void console_put_char(uint8_t char_asci);
void console_put_int(uint32_t num);
#endif // __DEVICE_CONSOLE_H__