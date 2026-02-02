#ifndef KPRINF_H
#define KPRINTF_H

#include <stdint.h>
#include <stdarg.h>

void init_kprintf();
void kputs(const char* str);
void kputchar(const char c);
void kprintf();
#endif
