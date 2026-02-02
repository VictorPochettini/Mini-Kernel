#include "vga.h"

static volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;
static uint32_t position;
static uint16_t character;
static uint16_t colour = (uint16_t) VGA_LIGHT_GREEN << 8;;
static uint16_t printed;

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
        character = (uint16_t) 'A';
        uint16_t alarm = character | colour;
        cursor_y++;
        cursor_x = 0;
        for(cursor_x; cursor_x < VGA_WIDTH; cursor_x++)
        {
            position = (cursor_y * VGA_WIDTH) + cursor_x;
            vga_buffer[position] = alarm;
        }
        return;
    }

    character = (uint16_t) c;
    printed = colour | character;
    
    position = (cursor_y * VGA_WIDTH) + cursor_x;
    vga_buffer[position] = printed;
    cursor_x++;

    if(cursor_x >= VGA_WIDTH)
    {
        cursor_y++;
        cursor_x = 0;
    }
}

void vga_clear()
{
    uint16_t blank = ' ' | (VGA_BLACK << 8);
    for(int i = 0; i < VGA_AREA; i++)
    {
        vga_buffer[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
}

void vga_write(const char* str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        vga_putchar(str[i]);
    }
}