#ifndef IODINE_INTERRUPTS_H
#define IODINE_INTERRUPTS_H

#include <stdint.h>

struct cpu_state {
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rbp;
	uint64_t rdi;
	uint64_t rsi;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;

	uint64_t int_no;
	uint32_t error_code;

	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
};

void interrupts_init();

#endif //IODINE_INTERRUPTS_H
