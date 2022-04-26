// stivale.c - Handles the stivale2 boot protocol.

// Resource: https://github.com/stivale/stivale/blob/master/STIVALE2.md

#include <stdint.h>
#include <stddef.h>
#include "../third-party/stivale/stivale2.h"
#include "common.h"
#include "stivale.h"

// Stivale terminal
static struct stivale2_header_tag_terminal terminal_header_tag = {
	.tag = {
		.identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
		.next = 0
	},
	.flags = 0
};

// Stivale framebuffer
static struct stivale2_header_tag_framebuffer framebuffer_header_tag = {
	.tag = {
		.identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
		.next = (uint64_t) &terminal_header_tag
	},
	// Let the bootloader pick the best framebuffer options
	.framebuffer_width = 0,
	.framebuffer_height = 0,
	.framebuffer_bpp = 0
};

__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_header = {
	.entry_point = 0, // Use the ELF entry point
	.stack = (uintptr_t) stack + sizeof(stack),

	// Bit 1: Get higher-half pointers from the bootloader, since we're a higher-half kernel
	// Bit 2: Enable protected memory ranges, to respect the permissions from the ELF header
	// Bit 3: Enable fully virtual kernel mappings, so we can sit anywhere in physical memory
	// Bit 4: Disable deprecated feature, should always be set
	.flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),

	// This is a linked list, the first element points to the next element and so on.
	.tags = (uintptr_t) &framebuffer_header_tag
};

// Helper function to get tags from the bootloader.
void* stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
	struct stivale2_tag* current_tag = (void*) stivale2_struct->tags;
	while (1) {
		// We reached the end and did not find the tag.
		if (current_tag == NULL) return NULL;

		// We found the tag.
		if (current_tag->identifier == id) return current_tag;

		// Get the next tag.
		current_tag = (void*) current_tag->next;
	}
}
