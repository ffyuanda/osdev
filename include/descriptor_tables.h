#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H
#include <stdint.h>

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdtr;

typedef struct {
	uint16_t limit_low;  /* seg limit bits 0 to 15 */
	uint16_t base_low;   /* seg base bits 0 to 15*/
	uint8_t base_middle; /* seg base bits 16 to 23*/
	uint8_t access;      /* access byte: Type, S, DPL, P */
	uint8_t granularity; /* seg limit bits 16 to 19, AVL, L, D/B, G */
	uint8_t base_high;   /* seg base bits 24 to 31 */
} __attribute__((packed)) gdt_entry;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtr;

typedef struct {
	uint16_t base_low;  /* offset bits 0 to 15 */
	uint16_t sel;   	/* segment selector */
	uint8_t all_zeros;  /* always zeroes */
	uint8_t flags;      /* 0x00110, DPL, P */
	uint16_t base_high; /* offset bits 16 to 31 */
} __attribute__((packed)) idt_entry;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void init_descriptor_tables();

#endif
