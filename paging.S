.text
.global load_page_directory
.global enable_paging
load_page_directory:
# prologue
push %ebp
mov %esp, %ebp

mov 8(%esp), %eax
mov %eax, %cr3

# epilogue
mov %ebp, %esp
pop %ebp
ret

enable_paging:
# prologue
push %ebp
mov %esp, %ebp

mov %cr0, %eax
or $0x80000000, %eax
mov %eax, %cr0

# epilogue
mov %ebp, %esp
pop %ebp
ret
