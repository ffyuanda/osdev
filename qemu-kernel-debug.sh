#!/bin/sh
set -e
. ./headers.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" CFLAGS="-O0 -g" $MAKE -j install)
done

qemu-system-$(./target-triplet-to-arch.sh $HOST) -s -S -kernel sysroot/boot/myos.kernel &
gdb
