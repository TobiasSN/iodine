// log.c - Handles debug logging to screen and serial.

#include <stdint.h>
#include "log.h"
#include "port.h"
#include "serial.h"

#define LOG_SERIAL_PORT SERIAL_PORT_1

char* hex_digits = "0123456789ABCDEF";

void log_init() {
	serial_init_port(LOG_SERIAL_PORT);
}

void log_char(char c) {
	port_write_8(LOG_SERIAL_PORT, c);
}

void log_string(char* string) {
	char* current = string;
	while (*current != 0) {
		log_char(*current);
		current++;
	}
}

void log_number(uint64_t number) {
	if (number == 0) {
		log_char('0');
		return;
	}

	uint8_t encountered_nonzero = 0;
	for (uint64_t i = 1e19; i >= 1; i /= 10) {
		uint8_t digit = (number / i) % 10;
		if (digit != 0 || encountered_nonzero) {
			encountered_nonzero = 1;
			log_char('0' + digit);
		}
	}
}

void log_hex(uint64_t number, uint8_t nibbles) {
	log_string("0x");
	for (int i = (nibbles - 1) * 4; i >= 0; i -= 4) {
		uint8_t nibble = (number >> i) & 0b1111; // Extract 1 nibble at a time
		log_char(hex_digits[nibble]);
	}
}

void log_hex_8(uint8_t number) {
	log_hex(number, 2);
}

void log_hex_16(uint16_t number) {
	log_hex(number, 4);
}

void log_hex_32(uint32_t number) {
	log_hex(number, 8);
}

void log_hex_64(uint64_t number) {
	log_hex(number, 16);
}
