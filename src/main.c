#include <stdint.h>
#include <stdio.h>

static unsigned sum8_c(const uint8_t* p, unsigned n) {
  unsigned acc=0;
  for (unsigned i=0;i<n;i++) acc += p[i];
  return acc;
}

/* Unrolling ×4 — cztery elementy na iterację */
unsigned sum8_unroll4(const uint8_t* p, unsigned n) {
  unsigned acc=0;
  unsigned i=0;
  /* Główna pętla — 4 elementy na raz */
  while (i+3 < n) {
    acc += p[i++];
    acc += p[i++];
    acc += p[i++];
    acc += p[i++];
  }
  /* Reszta */
  while (i < n) {
    acc += p[i++];
  }
  return acc;
}

int main(void) {
  const unsigned S = 123; /* (nr_albumu % 1000) */
  const unsigned N = 500u + (S % 200u);
  static uint8_t buf[1024];
  for (unsigned i=0;i<N;i++) buf[i]=(uint8_t)((i*11u+5u)&0xFF);

  unsigned a = sum8_c(buf, N);
  unsigned b = sum8_unroll4(buf, N);

  printf("ex02: sum8_c=%u sum8_unroll4=%u\n", a, b);
  if (a==b) puts("OK [ex02]"); else puts("FAIL [ex02]");

  /* Prosty „pomiar” — wielokrotne wywołania (metryka czasopodobna) */
  volatile unsigned sink=0;
  for (unsigned k=0;k<100;k++) sink += sum8_unroll4(buf, N);
  printf("ex02: metric=%u\n", sink & 0xFFFF);

  return 0;
}
