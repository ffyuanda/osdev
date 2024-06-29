#ifndef MMU_H
#define MMU_H

#include <stdint.h>
extern void *_kernel_end;
extern void *kernel_end;

typedef uint32_t pde;
typedef uint32_t pte;
void init_paging();

struct free_frame_stack
{
	uint32_t cap;
	uint32_t len;
	uint32_t stack[];
};


#endif
