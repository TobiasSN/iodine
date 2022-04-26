# Iodine

Just a hobby OS, nothing special.

Contributions are not being accepted, as this is a personal project.

## Downloading, building and running

### Downloading

```sh
git clone --recurse-submodules git@github.com:/TobiasSN/iodine.git
```

### Building and running

**Note:** Building and running is only tested on macOS, and requires a Unix-like
environment.

Dependencies:
- x86_64-elf GCC and Binutils
- Native GCC (For `limine-deploy`)
- Make
- xorriso
- QEMU (Optional)

To run in QEMU:
```sh
make run
# Or with GDB (Attach on port 1234, waits for GDB):
DEBUG=1 make run
```

To build an ISO:
```sh
make iso
```

# License

Copyright (c) 2022 Tobias SN. All rights reserved.
