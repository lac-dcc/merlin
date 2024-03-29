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
       0            big-arr\n\
       1            big-arr-10x\n\
       2            empty\n\
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

__attribute__((used)) static void
qeth_l3_convert_addr_to_bits(u8 *addr, u8 *bits, int len) {
  unsigned counterqeth_l3_convert_addr_to_bits1 = 0;
  unsigned counterqeth_l3_convert_addr_to_bits0 = 0;

  int templen = len;

  int i, j;
  u8 octet;

  for (i = 0; i < len; ++i) {
    counterqeth_l3_convert_addr_to_bits0++;
    octet = addr[i];
    for (j = 7; j >= 0; --j) {
      counterqeth_l3_convert_addr_to_bits1++;
      bits[i * 8 + j] = octet & 1;
      octet >>= 1;
    }
  }

  printf("Number of counters: 2\n");
  printf("At line 66 :");
  printf(" len\n");
  printf("Nesting depth: 1\n");
  printf("At line 64 :");
  printf(" len\n");
  printf("Nesting depth: 1\n");
  printf("%d %d\n", templen, counterqeth_l3_convert_addr_to_bits1);
  printf("%d %d\n", templen, counterqeth_l3_convert_addr_to_bits0);
}

// ------------------------------------------------------------------------- //

int main(int argc, char *argv[]) {

  if (argc != 2) {
    usage();
    return 1;
  }

  int opt = atoi(argv[1]);
  switch (opt) {

  // big-arr
  case 0: {
    // static_instructions_O0 : 38
    // dynamic_instructions_O0 : 38516
    // -------------------------------
    // static_instructions_O1 : 22
    // dynamic_instructions_O1 : 14034
    // -------------------------------
    // static_instructions_O2 : 45
    // dynamic_instructions_O2 : 8681
    // -------------------------------
    // static_instructions_O3 : 45
    // dynamic_instructions_O3 : 8681
    // -------------------------------
    // static_instructions_Ofast : 45
    // dynamic_instructions_Ofast : 8681
    // -------------------------------
    // static_instructions_Os : 20
    // dynamic_instructions_Os : 13778
    // -------------------------------
    // static_instructions_Oz : 28
    // dynamic_instructions_Oz : 19138
    // -------------------------------

    int len = 255;

    int _len_addr0 = 65025;
    int *addr = (int *)malloc(_len_addr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_addr0; _i0++) {
      addr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_bits0 = 65025;
    int *bits = (int *)malloc(_len_bits0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_bits0; _i0++) {
      bits[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    qeth_l3_convert_addr_to_bits(addr, bits, len);
    free(addr);
    free(bits);

    break;
  }

  // big-arr-10x
  case 1: {
    int len = 10;

    int _len_addr0 = 100;
    int *addr = (int *)malloc(_len_addr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_addr0; _i0++) {
      addr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_bits0 = 100;
    int *bits = (int *)malloc(_len_bits0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_bits0; _i0++) {
      bits[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    qeth_l3_convert_addr_to_bits(addr, bits, len);
    free(addr);
    free(bits);

    break;
  }
  case 2: {
    int len = 100;

    int _len_addr0 = 10000;
    int *addr = (int *)malloc(_len_addr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_addr0; _i0++) {
      addr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_bits0 = 10000;
    int *bits = (int *)malloc(_len_bits0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_bits0; _i0++) {
      bits[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    qeth_l3_convert_addr_to_bits(addr, bits, len);
    free(addr);
    free(bits);

    break;
  }
  case 3: {
    int len = 150;

    int _len_addr0 = 22500;
    int *addr = (int *)malloc(_len_addr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_addr0; _i0++) {
      addr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_bits0 = 22500;
    int *bits = (int *)malloc(_len_bits0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_bits0; _i0++) {
      bits[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    qeth_l3_convert_addr_to_bits(addr, bits, len);
    free(addr);
    free(bits);

    break;
  }
  case 4: {
    int len = 200;

    int _len_addr0 = 40000;
    int *addr = (int *)malloc(_len_addr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_addr0; _i0++) {
      addr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_bits0 = 40000;
    int *bits = (int *)malloc(_len_bits0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_bits0; _i0++) {
      bits[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    qeth_l3_convert_addr_to_bits(addr, bits, len);
    free(addr);
    free(bits);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
