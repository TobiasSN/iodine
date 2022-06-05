// main.c - The kernel entry point.

#include "idt.h"
#include "interrupts.h"
#include "log.h"

void _start() {
	log_string("Welcome to Iodine!\n");

	interrupts_init();
	idt_init();

	while (1) {
		asm ("hlt");
	}
}
