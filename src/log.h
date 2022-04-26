// log.h - Handles debug logging.

#ifndef IODINE_LOG_H
#define IODINE_LOG_H

#include <stdint.h>

void log_init();

void log_char(char c);
void log_string(char* string);
void log_number(uint64_t number);
void log_hex_8(uint8_t number);
void log_hex_16(uint16_t number);
void log_hex_32(uint32_t number);
void log_hex_64(uint64_t number);

#endif //IODINE_LOG_H
