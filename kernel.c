#include <stdio.h>
#include "tty.h"
#include "descriptor_tables.h"
#include "mmu.h"

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	init_descriptor_tables();
	init_paging();
	printf("Hello, kernel World! AGAIN!\n");
	*(unsigned char *)(0x3FFFFF) = 'A';
	// asm volatile ("int $3");
}
