.global gdt_flush

gdt_flush:
	cli # disable interrupts
	mov 4(%esp), %eax
	lgdt (%eax)

	# data segments
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

	# change CS register by doing a far jump
	jmp $0x08, $load_cs
load_cs:
	ret
