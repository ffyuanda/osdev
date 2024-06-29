#ifndef MMU_H
#define MMU_H

#include <stdint.h>

#define ROUND_UP_4096(x) (((x) + 4095) & ~4095)
extern void *_kernel_end;
extern void *kernel_end;

typedef uint32_t pde;
typedef uint32_t pte;
void init_paging();

struct free_frame_stack
{
	uint32_t cap;
	uint32_t len;
	uint32_t stack[40000];
};

extern struct free_frame_stack free_stack;
void free_stack_init(uint32_t mem_upper);
void* alloc_phys_page();
void free_phys_page(void* addr);

#endif
