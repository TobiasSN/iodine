// panic.c - Handles kernel panics and outputs debug information.

#include "panic.h"
#include "log.h"

char* interrupt_names[] = {
	"Divide Error",
	"Debug Exception",
	"NMI",
	"Breakpoint",
	"Overflow",
	"BOUND Range Exceeded",
	"Invalid Opcode (Undefined Opcode)",
	"Device Not Available (No Math Coprocessor)",
	"Double Fault",
	"Reserved",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment Fault",
	"General Protection",
	"Page Fault",
	"Reserved",
	"x87 FPU Floating-Point Error (Math Fault)",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Control Protection Exception"
};

void log_register(char* name, uint64_t value) {
	log_string(name);
	log_char('=');
	log_hex_64(value);
	log_char(' ');
}

void panic(struct cpu_state* state) {
	log_string("--- KERNEL PANIC ---\n\n");
	log_string("Interrupt: ");
	log_number(state->int_no);
	log_char(' ');
	log_string(interrupt_names[state->int_no]);
	log_string("\nError code: ");
	log_number(state->error_code);
	log_string("\n\n");

	log_register("RAX", state->rax);
	log_register("RBX", state->rbx);
	log_register("RCX", state->rcx);
	log_register("RDX", state->rdx);
	log_char('\n');
	log_register("RSI", state->rsi);
	log_register("RDI", state->rdi);
	log_register("RBP", state->rbp);
	log_register(" R8", state->r8);
	log_char('\n');
	log_register(" R9", state->r9);
	log_register("R10", state->r10);
	log_register("R11", state->r11);
	log_register("R12", state->r12);
	log_char('\n');
	log_register("R13", state->r13);
	log_register("R14", state->r14);
	log_register("R15", state->r15);

	log_string("\n\n");
	log_register("RIP", state->rip);
	log_register("CS", state->cs);
	log_register("RFLAGS", state->rflags);
	log_register("RSP", state->rsp);

	// Prevent further interrupts
	asm ("cli");

	while (1) {
		asm ("hlt");
	}
}
