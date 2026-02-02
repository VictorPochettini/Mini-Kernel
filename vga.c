#include "vga.h"

static volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;
static uint32_t position;
static enum vga_colour current_colour = VGA_LIGHT_GREY;

void vga_putchar(const char c)
{
    if(c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    if(c == '\t')
    {
        cursor_x = (cursor_x + 4) & ~(4 - 1);
        return;
    }

    if(c == '\r')
    {
        cursor_x = 0;
        return;
    }

    if(c == '\0')
        return;

    if(c == '\a')
    {
        uint16_t character = (uint16_t) 'A';
        uint16_t colour = (uint16_t) VGA_WHITE << 8;
        uint16_t alarm = character | colour;
        cursor_y++;
        cursor_x = 0;
        for(cursor_x; cursor_x < VGA_WIDTH; cursor_x++)
        {
            position = (cursor_y * VGA_WIDTH) + cursor_x;
            vga_buffer[position] = alarm;
        }
    }
}