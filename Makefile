# Programs
CC := x86_64-elf-gcc
AS := nasm
QEMU := qemu-system-x86_64

# Directories
SRC_DIR := src
OUT_DIR := build
OBJECTS_DIR := build/objects
ROOT_DIR := $(OUT_DIR)/root
LIMINE_DIR := third-party/limine

# Files
LINKER_SCRIPT := linker.ld
KERNEL := $(OUT_DIR)/kernel.elf
ISO := $(OUT_DIR)/image.iso
LIMINE_INSTALL := $(LIMINE_DIR)/limine-install
ROOT_FILES := \
	$(KERNEL) \
	limine.cfg \
	$(LIMINE_DIR)/limine.sys \
	$(LIMINE_DIR)/limine-cd.bin \
	$(LIMINE_DIR)/limine-eltorito-efi.bin

# User controllable flags
CFLAGS ?= -O2 -g
ASFLAGS ?=
LDFLAGS ?=

# Internal flags that should not be overridden

CFLAGS := $(CFLAGS) \
	-I. \
	-std=gnu99 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-pic \
	-mabi=sysv \
	-mno-red-zone \
	-mcmodel=kernel \
	-mgeneral-regs-only \
	-MMD

ASFLAGS := $(ASFLAGS) \
	-f elf64

LDFLAGS := $(LDFLAGS) \
	-T$(LINKER_SCRIPT) \
	-nostdlib \
	-zmax-page-size=0x1000 \
	-static

XORRISO_FLAGS := \
	-as mkisofs \
	-b limine-cd.bin \
	-no-emul-boot \
	-boot-load-size 4 \
	-boot-info-table \
	--efi-boot limine-eltorito-efi.bin \
	-efi-boot-part \
	--efi-boot-image \
	--protective-msdos-label

ifeq ($(DEBUG),1)
# -s: Enable GDB, -S: Wait for GDB
QEMU_FLAGS := \
	-s \
	-S
else
QEMU_FLAGS := -serial stdio
endif

# Utility that ensures that the target's directory exists.
dir_guard = @mkdir -p $(@D)

C_FILES := $(shell find $(SRC_DIR) -type f -name "*.c")
ASM_FILES := $(shell find $(SRC_DIR) -type f -name "*.asm")
O_FILES := \
	$(patsubst $(SRC_DIR)/%.c,$(OBJECTS_DIR)/%.o,$(C_FILES)) \
	$(patsubst $(SRC_DIR)/%.asm,$(OBJECTS_DIR)/%.o,$(ASM_FILES))

.PHONY: all
all: iso

.PHONY: iso
iso: $(ISO)

$(ISO): $(ROOT_FILES) $(LIMINE_INSTALL)
	$(dir_guard)
	rm -rf $(ROOT_DIR)
	mkdir $(ROOT_DIR)
	cp -v $(ROOT_FILES) $(ROOT_DIR)/
	xorriso $(XORRISO_FLAGS) $(ROOT_DIR) -o $@
	$(LIMINE_INSTALL) $(ISO)

$(KERNEL): $(O_FILES)
	$(dir_guard)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.asm
	$(dir_guard)
	$(AS) $(ASFLAGS) -o $@ $<

$(LIMINE_INSTALL):
	$(MAKE) -C third-party/limine limine-install

.PHONY: run
run: iso
	$(QEMU) $(QEMU_FLAGS) $(ISO)

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/* $(OUT_DIR)/.*
