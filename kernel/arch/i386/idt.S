.global idt_flush
idt_flush:
	mov 4(%esp), %eax
	lidt (%eax)
	ret

.macro ISR_NOERRCODE vector
	.global isr\vector

	isr\vector:
		cli
		push $0    # push a dummy error code
		push $\vector # push the interrupt number
		jmp isr_common_stub
.endm

.macro ISR_ERRCODE vector
	.global isr\vector

	isr\vector:
		cli
		push $\vector # push the interrupt number
		jmp isr_common_stub
.endm


# construct ISRs
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8 # pushes error code
ISR_NOERRCODE 9
ISR_ERRCODE   10 # pushes error code
ISR_ERRCODE   11 # pushes error code
ISR_ERRCODE   12 # pushes error code
ISR_ERRCODE   13 # pushes error code
ISR_ERRCODE   14 # pushes error code
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

# in isr.c
.extern isr_handler

# This is our common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.
isr_common_stub:
	// pusha # push all general registers

	// mov %ds, %ax
	// push %eax # save the data segment descriptor

	// mov $0x10, %ax # load the kernel data segment descriptor
	// mov %ax, %ds
	// mov %ax, %es
	// mov %ax, %fs
	// mov %ax, %gs

	call isr_handler

	// pop %eax # restore the original data segment descriptor
	// mov %ax, %ds
	// mov %ax, %es
	// mov %ax, %fs
	// mov %ax, %gs

	// popa # restore all general registers
	add $8, %esp # clean up the pushed error code and ISR number
	sti # enable interrupt
	iret # return from interrupt
