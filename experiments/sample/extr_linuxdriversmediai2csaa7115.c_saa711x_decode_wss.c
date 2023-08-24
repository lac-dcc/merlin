// ========================================================================= //

// includes
#include "float.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define JOTAI_NUM_RANDS_ 25

const unsigned rand_primes[JOTAI_NUM_RANDS_] = {
    179,   103,   479,    647,    229,    37,     271,   557,   263,
    607,   18743, 50359,  21929,  48757,  98179,  12907, 52937, 64579,
    49957, 52567, 507163, 149939, 412157, 680861, 757751};

int next_i() {
  int counter = 0;
  return rand_primes[(++counter) % JOTAI_NUM_RANDS_];
}

float next_f() {
  int counter = 0;
  return rand_primes[(++counter) % JOTAI_NUM_RANDS_] / 757751.0F;
}

// Usage menu
void usage() {
  printf("%s", "Usage:\n\
    prog [ARGS]\n\
\nARGS:\n\
       0            big-arr-10x\n\
\n\
");
}

// ------------------------------------------------------------------------- //

#define NULL ((void *)0)
typedef unsigned long size_t; // Customize by platform.
typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef long scalar_t__; // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef int u8;

/* Variables and functions */

__attribute__((used)) static int saa711x_decode_wss(u8 *p) {
  unsigned countersaa711x_decode_wss0 = 0;

  static const int wss_bits[8] = {0, 0, 0, 1, 0, 1, 1, 1};
  unsigned char parity;
  int wss = 0;
  int i;

  for (i = 0; i < 16; i++) {
    countersaa711x_decode_wss0++;
    int b1 = wss_bits[p[i] & 7];
    int b2 = wss_bits[(p[i] >> 3) & 7];

    if (b1 == b2) {

      printf("1\n");
      printf("at line 63 :");
      printf("\n");
      printf("%d\n", countersaa711x_decode_wss0);
      return -1;
    }
    wss |= b2 << i;
  }
  parity = wss & 15;
  parity ^= parity >> 2;
  parity ^= parity >> 1;

  if (!(parity & 1)) {

    printf("1\n");
    printf("at line 63 :");
    printf("\n");
    printf("%d\n", countersaa711x_decode_wss0);
    return -1;
  }

  printf("1\n");
  printf("at line 63 :");
  printf("\n");
  printf("%d\n", countersaa711x_decode_wss0);
  return wss;
}

// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //

int main(int argc, char *argv[]) {

  if (argc != 2) {
    usage();
    return 1;
  }

  int opt = atoi(argv[1]);
  switch (opt) {

  // big-arr-10x
  case 0: {
    int _len_p0 = 100;
    int *p = (int *)malloc(_len_p0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_p0; _i0++) {
      p[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = saa711x_decode_wss(p);
    printf("%d\n", benchRet);
    free(p);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
