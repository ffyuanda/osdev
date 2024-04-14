#include "mmu.h"

pde page_directory[1024] __attribute__((aligned(4096)));
pte first_page_table[1024] __attribute__((aligned(4096)));

extern void load_page_directory();
extern void enable_paging();

void init_page_table() {
	uint32_t i = 0;
	for (i = 0; i < 1024; ++i) {
		// present, allows write, kernel only
		first_page_table[i] = (i * 0x1000) | 0x3;
	}
}

void init_page_directory() {
	uint32_t i = 0;
	for (i = 0; i < 1024; ++i) {
		// not present, allows write, kernel only
		page_directory[i] = 0x2;
	}
	init_page_table();
	// present, allows write, kernel only
	page_directory[0] = ((uint32_t)first_page_table | 3);
}

void init_paging() {
	init_page_directory();
	load_page_directory(page_directory);
	enable_paging();
}
