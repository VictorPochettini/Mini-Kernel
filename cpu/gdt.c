#include "gdt.h"
#include <stdint.h>

static inline struct gdt_entry set_gdt_entry(uint32_t limit, uint32_t base, uint8_t access, uint8_t flags)
{
	struct gdt_entry entry;
	
	entry.limit_low =  ((uint16_t) limit) & 0xFFFF;
	entry.base_low = base & 0xFFFF;
	entry.base_middle = ((uint8_t)(base >> 16)) & 0xFF;
	entry.access = access;
	entry.granularity = (flags << 4) | ((uint8_t)(limit >> 16));
	entry.base_high = (base >> 24) & 0xFF;

	return entry;
}

struct gdt_entry* init_gdt()
{
	//Null Descriptor
	uint32_t limit_null = 0x00000000;
	uint32_t base_null = 0x00000000;
	uint8_t access_null = 0x00;
	uint8_t flags_null = 0x00;
	struct gdt_entry null_entry = set_gdt_entry(limit_null, base_null, access_null, flags_null);

	//Kernel Mode Code Segment
	uint32_t limit_KMCS = 0x000FFFFF;
	uint32_t base_KMCS = 0x00000000;
	uint8_t access_KMCS = 0x9A;
	uint8_t flags_KMCS = 0x0C;
	struct gdt_entry KMCS_entry = set_gdt_entry(limit_KMCS, base_KMCS, access_KMCS, flags_KMCS);

	//Kernel Mode Data Segment
	uint32_t limit_KMDS = 0x000FFFFF;
	uint32_t base_KMDS = 0x00000000;
	uint8_t access_KMDS = 0xFA;
	uint8_t	flags_KMDS = 0x0C;
	struct gdt_entry KMDS_entry = set_gdt_entry(limit_KMDS, base_KMDS, access_KMDS, flags_KMDS);

	struct gdt_entry* gdt = (struct gdt_entry*) 0x1000;
	gdt[0] = null_entry;
	gdt[1] = KMCS_entry;
	gdt[2] = KMDS_entry;

	return gdt;
}

struct gdtr init_gdtr()
{
	struct gdtr gdtr;
	gdtr.limit = sizeof(gdtr) - 1;
	gdtr.base = (uint32_t)&gdtr;

	return gdtr;
}
