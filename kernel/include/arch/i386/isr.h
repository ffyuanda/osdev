#ifndef ISR_H
#define ISR_H
#include <stdint.h>

typedef struct
{
	uint32_t ds; /* data segment selector */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by pusha */
	uint32_t int_no, err_code; /* interrupt number and error code */
	uint32_t eip, cs, eflags, useresp, ss; /* pushed by the processor automatically */
} registers_t;


#endif
