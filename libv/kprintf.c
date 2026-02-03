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

void kprint_int(int v)
{
    if(v < 0)
    {
        kputchar('-');
        v = -v;
    }

    int acc = 0;
    int aux = v;

    while(aux >= 10)
    {
        aux /= 10;
        acc++;
    }

    for(int i = 0; i <= acc; i++)
    {
        kputchar(int_to_char(v / power(10, (acc - i))));
    }
}

static inline int power(int base, int exp)
{
    int result = 1;
    for(int i = 0; i < exp; i++)
        result *= base;
    return result;
}

static inline char int_to_char(int v)
{
    return 48 + (v % 10);
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
					int v = va_arg(args, int);
					kprint_int(v);
					break;
				case 'c':
					char c = (char) va_arg(args, int);
					kputchar(c);
					break;
				case 's':
					char* s = va_arg(args,  char*);
					kputs(s);
					break;	
			}
		}
		else
			kputchar(str[i]);
	}

    va_end(args);
}
