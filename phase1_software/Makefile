CC      = riscv64-elf-gcc
OBJCOPY = riscv64-elf-objcopy

CFLAGS  = -march=rv32i -mabi=ilp32 \
          -ffreestanding -nostdlib -nostartfiles -O2
LDFLAGS = -Wl,-T,linker.ld

all: mem.txt

prog.elf: start.S lif_main.c linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ start.S lif_main.c

prog.bin: prog.elf
	$(OBJCOPY) -O binary $< $@

mem.txt: prog.bin build_mem.py
	python3 build_mem.py

clean:
	rm -f prog.elf prog.bin mem.txt