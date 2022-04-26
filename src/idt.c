// idt.c - Sets up the Interrupt Descriptor Table to receive interrupts.

#include "idt.h"
#include <stdint.h>

static struct interrupt_descriptor idt[256];

static struct descriptor_table_pointer interrupt_descriptor_table_pointer = {
	.base = (uint64_t) &idt,
	.limit = sizeof(idt)
};


void idt_init() {
	asm ("lidt %0" : : "m" (interrupt_descriptor_table_pointer));
}

void idt_register(uint8_t number, void (handler)(), enum gate_type type) {
	struct interrupt_descriptor* entry;
	entry = &idt[number];

	uint64_t handler_address = (uint64_t) handler;

	entry->offset_1 = (uint16_t) handler_address;
	entry->offset_2 = (uint16_t) (handler_address >> 16);
	entry->offset_3 = (uint32_t) (handler_address >> 32);
	entry->selector = 0x28; // Stivale 64-bit code descriptor
	entry->interrupt_stack_table_offset = 0;
	entry->attributes = 0b10001110 | type; // No Interrupt Stack Table
	entry->reserved = 0;
}
