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