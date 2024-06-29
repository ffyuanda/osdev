#include "mmu.h"
#include "stdio.h"
#include "stddef.h"

void *kernel_end = &_kernel_end;

struct free_frame_stack free_stack;
void free_stack_init(uint32_t mem_upper) {
	mem_upper <<= 10; // convert mem_upper from kilobytes to bytes
	free_stack.cap = (mem_upper - (uint32_t)kernel_end) / (1 << 12);
	free_stack.len = 0;
	printf("free_stack.cap=%d", free_stack.cap);

	size_t i = 0;
	for (uint32_t addr = ROUND_UP_4096((uint32_t)kernel_end); addr < mem_upper; addr += 4096) {
		free_stack.stack[i++] = addr;
	}
	free_stack.len = i;
}

void* alloc_phys_page() {
	return (void*)free_stack.stack[--free_stack.len];
}

void free_phys_page(void* addr) {
	free_stack.stack[free_stack.len++] = (uint32_t) addr;
}

