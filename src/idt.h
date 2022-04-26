#ifndef IODINE_IDT_H
#define IODINE_IDT_H

#include <stdint.h>

struct interrupt_descriptor {
	uint16_t offset_1;
	uint16_t selector;
	uint8_t interrupt_stack_table_offset;
	uint8_t attributes;
	uint16_t offset_2;
	uint32_t offset_3;
	uint32_t reserved;
};

struct descriptor_table_pointer {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed));

enum gate_type {
	GATE_TYPE_INTERRUPT = 0,
	GATE_TYPE_TRAP = 1
};

struct interrupt_args {};

void idt_init();

void idt_register(uint8_t number, void (handler)(), enum gate_type type);

#endif //IODINE_IDT_H
