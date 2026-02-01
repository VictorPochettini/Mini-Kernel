void kernel_main(void)
{
	volatile char* vga = (char*)0xB8000;
	vga[0] = 'O';
	vga[1] = 0x0F;
	vga[2] = 'K';
	vga[3] = 0x0F;
	for(;;)
		__asm__("hlt");
}
