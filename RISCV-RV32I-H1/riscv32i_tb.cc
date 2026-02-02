#include "riscv32i.h"
#include <stdio.h>
#include <stdint.h>

#define RESULT_IDX (0x0F00 >> 2)
#define DONE_IDX   (0x0F04 >> 2)
#define DONE_MAGIC 0xDEADBEEF

int main(void) {
    arch_t mem[MEM_SIZE];
    ap_uint<4> wstrb;
    strb_t* pstrb = &wstrb;

    // Load mem.txt
    FILE* fptr = fopen("mem.txt", "r");
    if (!fptr) { perror("mem.txt open failed"); return 1; }

    unsigned int tmp;
    int i = 0;
    while (i < MEM_SIZE && fscanf(fptr, "%x", &tmp) == 1) {
        mem[i++] = tmp;
    }
    for (; i < MEM_SIZE; i++) mem[i] = 0;
    fclose(fptr);

    // Clear mailboxes
    mem[RESULT_IDX] = 0;
    mem[DONE_IDX]   = 0;

    // Run CPU (returns on ECALL)
    cpu(mem, pstrb);

    uint32_t done = (uint32_t)mem[DONE_IDX];
    uint32_t hash = (uint32_t)mem[RESULT_IDX];
    printf("DONE=%08x HASH=%08x\n", done, hash);

    const uint32_t EXPECTED_HASH = 0x????????; // fill after you compute golden

    if (done != DONE_MAGIC) { printf("FAIL: no DONE\n"); return 1; }
    if (hash != EXPECTED_HASH) { printf("FAIL: hash mismatch\n"); return 1; }

    printf("PASS\n");
    return 0;
}