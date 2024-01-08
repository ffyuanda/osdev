#include <arch/i386/descriptor_tables.h>
#include <stdio.h>
#include <string.h>

/* defined in ASM */
extern void gdt_flush(uint32_t addr);
extern void idt_flush(uint32_t addr);

gdt_entry gdt_entries[5];
gdtr gdt_ptr;

idt_entry idt_entries[256];
idtr idt_ptr;

static void gdt_set_entry(uint16_t num, uint32_t base,
						  uint32_t limit, uint8_t access,
						  uint8_t gran) {
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access      = access;
}

static void init_gdt() {
	gdt_ptr.limit = sizeof(gdt_entry) * 5 - 1;
	gdt_ptr.base = (uint32_t) &gdt_entries;
	gdt_set_entry(0, 0, 0, 0, 0);                // Null segment
	gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	gdt_flush((uint32_t)&gdt_ptr);
}

static void idt_set_entry(uint16_t num, uint32_t base,
						  uint16_t sel, uint8_t flags) {
	idt_entries[num].base_low    = (base & 0xFFFF);
	idt_entries[num].base_high   = (base >> 16) & 0xFFFF;

	idt_entries[num].sel   		 = sel;
	idt_entries[num].all_zeros   = 0;

	// We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
	idt_entries[num].flags   	 = flags /* | 0x60 */;
}

static void init_idt() {
	idt_ptr.limit = sizeof(idt_entry) * 256 - 1;
	idt_ptr.base  = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry) * 256);
	idt_set_entry(0, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_entry(1, (uint32_t)isr1, 0x08, 0x8E);
	idt_set_entry(2, (uint32_t)isr2, 0x08, 0x8E);
	idt_set_entry(3, (uint32_t)isr3, 0x08, 0x8E);
	idt_set_entry(4, (uint32_t)isr4, 0x08, 0x8E);
	idt_set_entry(5, (uint32_t)isr5, 0x08, 0x8E);
	idt_set_entry(6, (uint32_t)isr6, 0x08, 0x8E);
	idt_set_entry(7, (uint32_t)isr7, 0x08, 0x8E);
	idt_set_entry(8, (uint32_t)isr8, 0x08, 0x8E);
	idt_set_entry(9, (uint32_t)isr9, 0x08, 0x8E);
	idt_set_entry(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_entry(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_entry(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_entry(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_entry(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_entry(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_entry(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_entry(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_entry(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_entry(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_entry(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_entry(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_entry(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_entry(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_entry(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_entry(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_entry(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_entry(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_entry(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_entry(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_entry(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_entry(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_flush((uint32_t)&idt_ptr);
	asm volatile ("sti");
}

void init_descriptor_tables() {
	init_gdt();
	printf("Initialized GDT.\n");

	init_idt();
	printf("Initialized IDT.\n");
}

