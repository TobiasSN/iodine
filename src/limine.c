// limine.c - Contains requests for the Limine boot protocol.

#include "../third-party/limine/limine.h"

// Dummy request so the bootloader can detect that we want the Limine protocol.
volatile struct limine_kernel_address_request dummy_request = {
	.id = LIMINE_KERNEL_ADDRESS_REQUEST,
	.revision = 0
};
