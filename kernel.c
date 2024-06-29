#include <stdio.h>
#include "tty.h"
#include "descriptor_tables.h"
#include "mmu.h"
#include "multiboot.h"

void kernel_main(struct multiboot_info *mb_info, uint32_t magic) {
	terminal_initialize();
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		printf("Error: MULTIBOOT_BOOTLOADER_MAGIC is incorrect: 0x%x\n", magic);
	printf("Upper available memory: %d\n", mb_info->mem_upper);
	printf("Hello, kernel World!\n");
	init_descriptor_tables();
	init_paging();
	printf("Hello, kernel World! AGAIN!\n");
	printf("kernel end: %x", kernel_end);
	*(unsigned char *)(0x3FFFFF) = 'A';
	// asm volatile ("int $3");
}
