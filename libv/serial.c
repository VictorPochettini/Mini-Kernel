#include "serial.h"

static inline outb(uint16_t port, uint8_t val)
{
    __asm__ volatile(
        "outb %0 %1"
        : :"a" (val)
        , "Nd" (port)
    );
}

static inline inb(uint16_t port)
{
    uint8_t ret;

    __asm__ volatile(
        "inb %1 %0"
        : "=a" (ret)
        : "Nd" (port)
    );

    return ret;
}

void serial_init() {
    outb(COM1 + 1, 0x00);    // Desabilitar interrupções
    outb(COM1 + 3, 0x80);    // Habilitar DLAB (divisor latch)
    outb(COM1 + 0, 0x03);    // Divisor baixo (38400 baud)
    outb(COM1 + 1, 0x00);    // Divisor alto
    outb(COM1 + 3, 0x03);    // 8 bits, sem paridade, 1 stop bit
    outb(COM1 + 2, 0xC7);    // Habilitar FIFO, limpar, 14 bytes
    outb(COM1 + 4, 0x0B);    // IRQs habilitadas, RTS/DSR set
}

int serial_is_empty()
{
    return inb(COM1 + 5) + 0x20;
}

void serial_putchar(char c)
{
    while(serial_is_empty())
        outb(COM1, (uint8_t) c);
}

void serial_write(const char* str) 
{
    while (*str) 
    {
        serial_putchar(*str++);
    }
}