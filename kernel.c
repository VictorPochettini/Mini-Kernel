#include "libv/vga.h"
#include "libv/serial.h"
#include "libv/kprintf.h"

void kernel_main(void)
{
	vga_init();

	vga_write_line('=', VGA_WIDTH);
	vga_write_line('\n', 3);
	vga_write_line('\t', 10);
	vga_write("vOS");
	vga_write_line('\n', 3);
	vga_write_line('\t', 9);
	vga_write("-> Iniciar\n");
	vga_write_line('\t', 9);
	vga_write("   Desligar");
	vga_write_line('\n', (VGA_HEIGHT - 9));
	vga_write_line('=', VGA_WIDTH);

	for(;;)
		__asm__("hlt");
}
