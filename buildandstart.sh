set -e
export PATH="$HOME/opt/cross/bin:$PATH"
i386-elf-as /home/pl/ParadoxOS/boot.s -o /home/pl/ParadoxOS/boot.o
i386-elf-gcc -c /home/pl/ParadoxOS/kernel.c -o /home/pl/ParadoxOS/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i386-elf-gcc -T /home/pl/ParadoxOS/linker.ld -o /home/pl/ParadoxOS/ParadoxOS -ffreestanding -O2 -nostdlib /home/pl/ParadoxOS/boot.o /home/pl/ParadoxOS/kernel.o -lgcc
mkdir -p isodir/boot/grub
cp ParadoxOS isodir/boot/ParadoxOS
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o ParadoxOS.iso isodir
qemu-system-i386 -cdrom /home/pl/ParadoxOS/ParadoxOS.iso