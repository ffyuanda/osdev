#include <arch/i386/isr.h>
#include <stdio.h>

void isr_handler(registers_t regs) {
	printf("received interrupt: %d\n", regs.int_no);
}
