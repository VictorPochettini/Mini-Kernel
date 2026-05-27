#ifndef idt_h
#define idt_h

#include <stdint.h>

struct idt_entry {
    uint16_t offset_low;     // offset bits 0..15
    uint16_t selector;       // seletor de segmento de código na GDT
    uint8_t  zero;           // reservado, sempre 0
    uint8_t  type_attributes; // gate type, dpl, e p
    uint16_t offset_high;    // offset bits 16..31
} __attribute__((packed));

struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#endif