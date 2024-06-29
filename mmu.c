#include "mmu.h"

void *kernel_end = &_kernel_end;

struct free_frame_stack free_stack;
void phys_frame_alloc_init(uint32_t mem_upper) {
	free_stack.cap = mem_upper - (uint32_t)kernel_end;
	free_stack.len = 0;
	// free_stack.stack = 4;
	uint32_t arr[mem_upper - (uint32_t)kernel_end];
	arr[0] = 1;

}