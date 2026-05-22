#!/bin/bash
set -e

export PATH="$HOME/opt/cross/bin:$PATH"

PROJECT=/home/pl/ParadoxOS
BUILD=$PROJECT/build
ISO=$PROJECT/isodir

mkdir -p $BUILD

echo "[1/5] Cleaning build directory..."
rm -f $BUILD/*.o
rm -f $BUILD/ParadoxOS
rm -f $BUILD/ParadoxOS.iso

# -------------------------
# Bootloader
# -------------------------
echo "[2/5] Assembling boot.s..."
i386-elf-as $PROJECT/boot/boot.s -o $BUILD/boot.o

# -------------------------
# Compile all C files
# -------------------------
echo "[3/5] Compiling C sources..."

CFILES=$(find $PROJECT \
  -path "$PROJECT/build" -prune -o \
  -path "$PROJECT/isodir" -prune -o \
  -name "*.c" -print)

for file in $CFILES; do
  name=$(basename "$file")
  obj="$BUILD/${name%.c}.o"

  i386-elf-gcc -c "$file" -o "$obj" \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I$PROJECT
done

# -------------------------
# Link kernel
# -------------------------
echo "[4/5] Linking kernel..."

OBJS=$(find $BUILD -name "*.o")

i386-elf-gcc \
-T $PROJECT/boot/linker.ld \
-o $BUILD/ParadoxOS \
-ffreestanding \
-O2 \
-nostdlib \
$OBJS \
-lgcc

# -------------------------
# Build ISO
# -------------------------
echo "[5/5] Building ISO..."

mkdir -p $ISO/boot/grub

cp $BUILD/ParadoxOS $ISO/boot/ParadoxOS
cp $PROJECT/grub.cfg $ISO/boot/grub/grub.cfg

grub-mkrescue -o $BUILD/ParadoxOS.iso $ISO

echo "Done."

# -------------------------
# Run
# -------------------------
qemu-system-i386 \
  -cdrom $BUILD/ParadoxOS.iso \
  -m 512 \
  -serial stdio \
  -vga std