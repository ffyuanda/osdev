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

void init_descriptor_tables();

#endif
