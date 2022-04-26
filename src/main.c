// main.c - The kernel entry point.

#include <stddef.h>
#include "../third-party/stivale/stivale2.h"
#include "stivale.h"
#include "idt.h"
#include "interrupts.h"
#include "log.h"

void (*term_write)(const char* string, size_t length);

void _start(struct stivale2_struct* stivale2_struct) {
	log_string("Welcome to Iodine!\n");

	interrupts_init();
	idt_init();

	while (1) {
		asm ("hlt");
	}
}
