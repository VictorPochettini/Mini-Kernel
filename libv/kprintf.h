#ifndef KPRINF_H
#define KPRINTF_H

#include <stdint.h>
#include <stdarg.h>

void init_kprintf();
void kputs(const char* str);
void kprintf(const char* str, ...);
inline void kputchar(const char c);
#endif
