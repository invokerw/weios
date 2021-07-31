#ifndef __KERNEL_MEMORY_H__
#define __KERNEL_MEMORY_H__
#include "stdint.h"
#include "bitmap.h"

enum pool_flags {
    PF_KERNEL = 1,
    PF_USER = 2
};

#define	 PG_P_1	  1	// 页表项或页目录项存在属性位
#define	 PG_P_0	  0	// 页表项或页目录项存在属性位
#define	 PG_RW_R  0	// R/W 属性位值, 读/执行
#define	 PG_RW_W  2	// R/W 属性位值, 读/写/执行
#define	 PG_US_S  0	// U/S 属性位值, 系统级
#define	 PG_US_U  4	// U/S 属性位值, 用户级

// 虚拟地址管理
struct virtual_addr {
    struct bitmap vaddr_bitmap; // 虚拟地址用到的位图结构，用于记录哪些虚拟地址被占用了。以页为单位。
    uint32_t vaddr_start; // 管理的虚拟地址
};

extern struct pool kernel_pool, user_pool;
void mem_init(void);
void* get_kernel_pages(uint32_t pg_cnt);
void* malloc_page(enum pool_flags pf, uint32_t pg_cnt);
void malloc_init(void);
uint32_t* pte_ptr(uint32_t vaddr);
uint32_t* pde_ptr(uint32_t vaddr);
uint32_t addr_v2p(uint32_t vaddr);
void* get_a_page(enum pool_flags pf, uint32_t vaddr);
void* get_user_pages(uint32_t pg_cnt);
#endif // __KERNEL_MEMORY_H__