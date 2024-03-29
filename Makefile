HOST=i686-elf
SYSROOT=$(shell pwd)/sysroot
PREFIX=/usr
BOOTDIR=/boot
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

AR=$(HOST)-ar
AS=$(HOST)-as
CC=$(HOST)-gcc

CC:=$(CC) --sysroot=$(SYSROOT)

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

KERNEL_OBJS=\
boot.o \
tty.o \
kernel.o \

OBJS=\
crti.o \
crtbegin.o \
$(KERNEL_OBJS) \
crtend.o \
crtn.o \
gdt.o \
descriptor_tables.o \
isr.o \
idt.o \

LIBK_OBJS=\
$(ARCH_FREEOBJS) \
printf.o \
putchar.o \
puts.o \
abort.o \
memcmp.o \
memcpy.o \
memmove.o \
memset.o \
strlen.o \
itoa.o \

LIBK_OBJS:=$(LIBK_OBJS:.o=.libk.o)

LINK_LIST=\
$(LDFLAGS) \
crti.o \
crtbegin.o \
$(KERNEL_OBJS) \
gdt.o \
descriptor_tables.o \
isr.o \
idt.o \
$(LIBS) \
crtend.o \
crtn.o \

.PHONY: all clean install install-headers install-kernel install-libs run
.SUFFIXES: .o .c .S .libk.o

all: $(LIBK_OBJS) myos.kernel

myos.kernel: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot myos.kernel

crtbegin.o crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

%.o: %.c
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.S
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

%.libk.o: %.c
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

%.libk.o: %.S
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f myos.kernel myos.iso
	rm -f libk.a
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d
	rm -rf sysroot isodir

install-headers:
	mkdir -p $(SYSROOT)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(SYSROOT)$(INCLUDEDIR)/.

install-libs: libk.a
	mkdir -p $(SYSROOT)$(LIBDIR)
	cp libk.a $(SYSROOT)$(LIBDIR)

install-kernel: myos.kernel
	mkdir -p $(SYSROOT)$(BOOTDIR)
	cp myos.kernel $(SYSROOT)$(BOOTDIR)

install: install-headers install-libs install-kernel
	mkdir -p isodir
	mkdir -p isodir/boot
	mkdir -p isodir/boot/grub
	cp $(SYSROOT)$(BOOTDIR)/myos.kernel isodir/boot/myos.kernel
	cp grub.cfg isodir/boot/grub/grub.cfg	
	grub-mkrescue -o myos.iso isodir

run: install
	qemu-system-i386 -cdrom myos.iso

debug: install
	qemu-system-i386 -s -S -kernel myos.kernel &
	gdb

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
