// serial.c - Handles initialization of serial ports.

// Resource: https://wiki.osdev.org/Serial_Ports

#include "serial.h"
#include "port.h"

void serial_init_port(uint16_t port) {
	port_write_8(port + 1, 0); // Disable interrupts
	port_write_8(port + 3, 0b10000000); // Enable DLAB
	port_write_8(port + 0, 1); // Set divisor to 0
	port_write_8(port + 1, 0); // ^
	port_write_8(port + 3, 0b10000011); // Disable DLAB, 8 data bits, 1 stop bit, no parity
}
