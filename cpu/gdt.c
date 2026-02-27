struct gdt_entry
{
	//I wanted to use uint_32 base but apparently it wouldn't work

	uint16_t limit_low;      // Limit bits 0-15 (16 bits)
    	uint16_t base_low;       // Base bits 0-15 (16 bits)
    	uint8_t  base_middle;    // Base bits 16-23 (8 bits)
    	uint8_t  access;         // Access byte (8 bits)
    	uint8_t  granularity;    // Flags (4 bits) + Limit bits 16-19 (4 bits)
    	uint8_t  base_high;      // Base bits 24-31 (8 bits)
}__attribute__((packed));

void gdt_init()
{
}
