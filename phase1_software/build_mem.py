#!/usr/bin/env python3
"""
Convert a raw RISC-V binary into a word-addressed mem.txt
compatible with the RV32I HLS testbench.

Input : prog.bin (little-endian)
Output: mem.txt  (one 32-bit hex word per line)
"""

import sys
from pathlib import Path

BIN_FILE = Path("prog.bin")
OUT_FILE = Path("mem.txt")

def main():
    if not BIN_FILE.exists():
        print(f"Error: {BIN_FILE} not found")
        sys.exit(1)

    data = BIN_FILE.read_bytes()

    # Pad to 32-bit word boundary
    if len(data) % 4:
        data += b'\x00' * (4 - len(data) % 4)

    with OUT_FILE.open("w") as f:
        for i in range(0, len(data), 4):
            w = (
                data[i]
                | (data[i+1] << 8)
                | (data[i+2] << 16)
                | (data[i+3] << 24)
            )
            f.write(f"{w:08x}\n")

    print(f"Wrote {OUT_FILE} ({len(data)//4} words)")

if __name__ == "__main__":
    main()