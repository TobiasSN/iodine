#ifndef IODINE_SERIAL_H
#define IODINE_SERIAL_H

#include <stdint.h>

#define SERIAL_PORT_1 0x03F8
#define SERIAL_PORT_2 0x02F8

void serial_init_port(uint16_t port);

#endif //IODINE_SERIAL_H
