; interrupt_handler.asm - Handles interrupts initially and hands them to C

bits 64

; This is a macro so it doesn't affect the stack.
%macro PUSH_REGISTERS 0
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push rbp
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro POP_REGISTERS 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rbp
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro ISR_ERROR_CODE 1
	global isr_%1

	isr_%1:
		push byte %1 ; Give the interrupt number to the handler
		jmp isr_common
%endmacro

%macro ISR_NO_ERROR_CODE 1
	global isr_%1

	isr_%1:
		push byte 0 ; Dummy error code
		push byte %1 ; Give the interrupt number to the handler
		jmp isr_common
%endmacro

extern interrupt_handler

isr_common:
	PUSH_REGISTERS
    cld ; The SysV ABI requires that DF is cleared.
    mov rdi, rsp ; Give the handler a pointer to the registers on the stack.
    call interrupt_handler
    POP_REGISTERS
    iretq

ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7
ISR_ERROR_CODE 8
ISR_NO_ERROR_CODE 9
ISR_ERROR_CODE 10
ISR_ERROR_CODE 11
ISR_ERROR_CODE 12
ISR_ERROR_CODE 13
ISR_ERROR_CODE 14
ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_ERROR_CODE 17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_ERROR_CODE 21
