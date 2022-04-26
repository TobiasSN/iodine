// port.h - Handles port IO.

#ifndef IODINE_PORT_H
#define IODINE_PORT_H

#include <stdint.h>

static inline void port_write_8(uint16_t port, uint8_t value) {
	asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

static inline void port_write_16(uint16_t port, uint16_t value) {
	asm volatile ("outw %0, %1" : : "a" (value), "Nd" (port));
}

static inline void port_write_32(uint16_t port, uint32_t value) {
	asm volatile ("outl %0, %1" : : "a" (value), "Nd" (port));
}

static inline uint8_t port_read_8(uint16_t port) {
	uint8_t value;
	asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
	return value;
}

static inline uint16_t port_read_16(uint16_t port) {
	uint16_t value;
	asm volatile ("inw %1, %0" : "=a" (value) : "Nd" (port));
	return value;
}

static inline uint32_t port_read_32(uint16_t port) {
	uint32_t value;
	asm volatile ("inl %1, %0" : "=a" (value) : "Nd" (port));
	return value;
}

#endif //IODINE_PORT_H
