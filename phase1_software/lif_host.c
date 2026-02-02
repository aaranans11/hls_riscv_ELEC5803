#include <stdint.h>
#include <stdio.h>

static uint32_t xorshift32(uint32_t* s){
  uint32_t x = *s;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  *s = x;
  return x;
}

static uint32_t hash_update(uint32_t h, uint32_t x){
  h ^= x;
  h *= 16777619u;
  return h;
}

int main(void) {
  const int N = 16;
  const int T = 16;

  const int32_t THRESH = 200;
  const int32_t RESET  = 0;
  const int LEAK_SHIFT = 4;

  int32_t v[16] = {0};
  uint32_t spike[16*16] = {0};

  uint32_t seed = 1;

  for (int t = 0; t < T; ++t) {
    for (int n = 0; n < N; ++n) {
      int32_t in = (int32_t)(xorshift32(&seed) & 0x3F) - 31;

      int32_t vn = v[n];
      vn = vn + in - (vn >> LEAK_SHIFT);

      uint32_t s = 0;
      if (vn >= THRESH) { s = 1; vn = RESET; }

      v[n] = vn;
      spike[t*N + n] = s;
    }
  }

  uint32_t h = 2166136261u;
  for (int n = 0; n < N; ++n) h = hash_update(h, (uint32_t)v[n]);
  for (int k = 0; k < N*T; ++k) h = hash_update(h, spike[k]);

  printf("EXPECTED_HASH = 0x%08x\n", h);
  return 0;
}