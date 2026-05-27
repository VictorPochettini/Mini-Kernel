#include "idt.h"
#include <stdint.h>

static struct idt_entry idt[256];

extern void setIdt(uint16_t limit, uint32_t base);

static inline struct idt_entry setIdt_entry(uint16_t offset_low, uint16_t selector, uint8_t zero, uint8_t type_attributes, uint16_t offset_high)
{
    struct idt_entry entry;
    entry.offset_low = offset_low;
    entry.selector = selector;
    entry.zero = zero;
    entry.type_attributes = type_attributes;
    entry.offset_high = offset_high;
    return entry;
}

void init_idt()
{   
    for(int i = 0; i < 256; i++)
        idt[i] = setIdt_entry(0, 0, 0, 0, 0);

    setIdt(sizeof(idt) - 1, (uint32_t) idt);
}