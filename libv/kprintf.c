#include "kprintf.h"
#include "vga.h"
#include "serial.h"

void init_kprintf()
{
    serial_init();
    vga_init();
}

void kputchar(const char c)
{
    serial_putchar(c);
    vga_putchar(c);
}

void kputs(const char* str)
{
    while(*str)
        kputchar(*str++);
}

void kprintf(const char* str, ...)
{
	va_list args;
	va_start(args, str);

	for(int i = 0; str[i] ; i++)
	{
		if(str[i] == '%')
		{
			i++;
			switch(str[i])
			{
				case 'd':
					int v = va_args(args, int);
					kprint_int(v);
					break;
				case 'c':
					char c = (char) va_args(args, int);
					kputchar(c);
					break;
				case 's':
					char* s = va_args(args,  char*);
					kputs(s);
					break;	
			}
		}
		else
			kputc(str[i]);
	}
}
