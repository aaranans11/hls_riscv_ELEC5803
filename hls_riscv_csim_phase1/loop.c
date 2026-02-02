#include <stdint.h>

int main(void) {
    volatile uint32_t x1 = 100; // 0x64 (outer loop)
    while (x1 != 0) {
        x1 = x1 - 1;
    }
}