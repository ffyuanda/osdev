#include <stdio.h>
#include <kernel/tty.h>
#include <arch/i386/descriptor_tables.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	init_descriptor_tables();
	asm volatile ("int $3");
}
