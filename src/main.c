// main.c - The kernel entry point.

#include <stddef.h>
#include "../third-party/stivale/stivale2.h"
#include "stivale.h"
#include "idt.h"
#include "interrupts.h"

void (*term_write)(const char* string, size_t length);

void _start(struct stivale2_struct* stivale2_struct) {
	struct stivale2_struct_tag_terminal* terminal_tag;
	terminal_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);

	// Hang if terminal tag wasn't found.
	if (terminal_tag == NULL) {
		while(1) asm ("hlt");
	}

	term_write = (void*) terminal_tag->term_write;

	term_write("Welcome to Iodine!\n", 19);

	interrupts_init();
	idt_init();

	while (1) {
		asm ("hlt");
	}
}
