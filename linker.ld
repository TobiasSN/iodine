OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(_start)

/* Program headers, so that we get the correct MMU permissions from the bootloader */
PHDRS {
    null    PT_NULL    FLAGS(0);                   /* Null segment */
    text    PT_LOAD    FLAGS((1 << 0) | (1 << 2)); /* Execute + Read */
    rodata  PT_LOAD    FLAGS((1 << 2));            /* Read-only */
    data    PT_LOAD    FLAGS((1 << 1) | (1 << 2)); /* Read + Write */
}

SECTIONS {
    /* Places the kernel in the topmost 2 GiB of the address space for optimizations */
    . = 0xFFFFFFFF80000000;

    .text : {
        *(.text .text.*)
    } :text

    /* Move to the next memory page for read-only data */

    . += CONSTANT(MAXPAGESIZE);

    /* Ensure that the Stivale2 header doesn't get discarded */
    .stivale2hdr : {
        KEEP(*(.stivale2hdr))
    } :rodata

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    /* Move to next memory page for .data */
    . += CONSTANT(MAXPAGESIZE);

    .data : {
        *(.data .data.*)
    } :data

    .bss : {
        *(COMMON)
        *(.bss .bss.*)
    } :data
}
