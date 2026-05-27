#include "pic.h"
#include "../libv/serial.h"
#include <stdint.h>

void pic_remap()
{
    int mask1 = inb(PIC1_DATA); // save masks
    int mask2 = inb(PIC2_DATA); // save masks

    // ICW1: initialize PICs, telling them that ICW4 will be sent later
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    // ICW2: defines where IRQs are mapped in the IDT
    outb(PIC1_DATA, 0x20); // IRQ0-7  →  32-39
    outb(PIC2_DATA, 0x28); // IRQ8-15 →  40-47

    // ICW3: cascade configuration
    outb(PIC1_DATA, 0x04); // Master: slave in IRQ2
    outb(PIC2_DATA, 0x02); // Slave: id 2

    // ICW4: 8086 mode
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    // Restore masks
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}