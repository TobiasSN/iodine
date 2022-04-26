// main.c - The kernel entry point.

#include <stddef.h>
#include "../third-party/stivale/stivale2.h"
#include "stivale.h"
#include "idt.h"
#include "interrupts.h"
#include "log.h"

void (*term_write)(const char* string, size_t length);

__attribute__((interrupt))
void keyboard_handler(struct interrupt_args* something) {
	term_write("Hello, world!", 13);
	asm ("sti");
}

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
	log_number(207);
	log_string("\n");
	asm ("int3");
	while (1) {
		asm ("hlt");
	}
}
