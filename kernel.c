#include <stdio.h>
#include "tty.h"
#include "descriptor_tables.h"
#include "mmu.h"
#include "multiboot.h"

void kernel_main(struct multiboot_info *mb_info, uint32_t magic) {
	terminal_initialize();
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		printf("Error: MULTIBOOT_BOOTLOADER_MAGIC is incorrect: 0x%x\n", magic);
	printf("Upper available memory: %d\n", mb_info->mem_upper << 10);
	printf("Kernel end: %d\n", (uint32_t *)kernel_end);
	printf("Hello, kernel World!\n");
	free_stack_init(mb_info->mem_upper);
	uint32_t addr0 = (uint32_t)alloc_phys_page();
	uint32_t addr1 = (uint32_t)alloc_phys_page();
	printf("\nalloc'd addr: %d\n", addr0);
	printf("alloc'd addr: %d\n", addr1);
	free_phys_page((void*)addr0);
	free_phys_page((void*)addr1);
	addr0 = (uint32_t)alloc_phys_page();
	addr1 = (uint32_t)alloc_phys_page();
	printf("alloc'd addr: %d\n", addr0);
	printf("alloc'd addr: %d\n", addr1);


	// init_descriptor_tables();
	// init_paging();
	// printf("Hello, kernel World! AGAIN!\n");
	// printf("kernel end: %x", _kernel_end);
	
	*(unsigned char *)(0x3FFFFF) = 'A';
	// asm volatile ("int $3");
}
