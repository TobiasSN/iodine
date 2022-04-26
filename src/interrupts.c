// interrupts.c - Receives interrupts and calls the appropriate handler

#include <stdint.h>
#include "idt.h"
#include "interrupts.h"
#include "log.h"
#include "panic.h"

void division_error(struct cpu_state* state) {
	log_string("Division error!\n");
	while (1) {}
}

#define REGISTER_ISR(number, gate_type) {\
	extern void isr_##number();\
	idt_register(number, isr_##number, gate_type);\
}

void interrupts_init() {
	REGISTER_ISR(0, GATE_TYPE_TRAP)
	REGISTER_ISR(1, GATE_TYPE_TRAP)
	REGISTER_ISR(3, GATE_TYPE_TRAP)
	REGISTER_ISR(4, GATE_TYPE_TRAP)
	REGISTER_ISR(5, GATE_TYPE_TRAP)
	REGISTER_ISR(6, GATE_TYPE_TRAP)
	REGISTER_ISR(7, GATE_TYPE_TRAP)
	REGISTER_ISR(8, GATE_TYPE_TRAP)
	REGISTER_ISR(9, GATE_TYPE_TRAP)
	REGISTER_ISR(10, GATE_TYPE_TRAP)
	REGISTER_ISR(11, GATE_TYPE_TRAP)
	REGISTER_ISR(12, GATE_TYPE_TRAP)
	REGISTER_ISR(13, GATE_TYPE_TRAP)
	REGISTER_ISR(14, GATE_TYPE_TRAP)
	REGISTER_ISR(15, GATE_TYPE_TRAP)
	REGISTER_ISR(16, GATE_TYPE_TRAP)
	REGISTER_ISR(17, GATE_TYPE_TRAP)
	REGISTER_ISR(18, GATE_TYPE_TRAP)
	REGISTER_ISR(19, GATE_TYPE_TRAP)
	REGISTER_ISR(20, GATE_TYPE_TRAP)
	REGISTER_ISR(21, GATE_TYPE_TRAP)
}

void interrupt_handler(struct cpu_state* state) {
	panic(state);
}


