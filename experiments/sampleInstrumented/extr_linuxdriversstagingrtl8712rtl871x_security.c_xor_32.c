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
typedef int sint;

/* Variables and functions */

__attribute__((used)) static void xor_32(u8 *a, u8 *b, u8 *out) {
  unsigned counterxor_320 = 0;

  sint i;

  for (i = 0; i < 4; i++) {
    counterxor_320++;
    out[i] = a[i] ^ b[i];
  }

  printf("Number of counters: 1\n");
  printf("At line 62 :");
  printf("\n");
  printf("Nesting depth: 0\n");
  printf("%d\n", counterxor_320);
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
    // static_instructions_O0 : 23
    // dynamic_instructions_O0 : 70
    // -------------------------------
    // static_instructions_O1 : 12
    // dynamic_instructions_O1 : 30
    // -------------------------------
    // static_instructions_O2 : 16
    // dynamic_instructions_O2 : 16
    // -------------------------------
    // static_instructions_O3 : 16
    // dynamic_instructions_O3 : 16
    // -------------------------------
    // static_instructions_Ofast : 16
    // dynamic_instructions_Ofast : 16
    // -------------------------------
    // static_instructions_Os : 11
    // dynamic_instructions_Os : 29
    // -------------------------------
    // static_instructions_Oz : 12
    // dynamic_instructions_Oz : 35
    // -------------------------------

    int _len_a0 = 65025;
    int *a = (int *)malloc(_len_a0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_a0; _i0++) {
      a[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b0 = 65025;
    int *b = (int *)malloc(_len_b0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b0; _i0++) {
      b[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_out0 = 65025;
    int *out = (int *)malloc(_len_out0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_out0; _i0++) {
      out[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    xor_32(a, b, out);
    free(a);
    free(b);
    free(out);

    break;
  }

  // big-arr-10x
  case 1: {

    int _len_a0 = 100;
    int *a = (int *)malloc(_len_a0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_a0; _i0++) {
      a[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b0 = 100;
    int *b = (int *)malloc(_len_b0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b0; _i0++) {
      b[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_out0 = 100;
    int *out = (int *)malloc(_len_out0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_out0; _i0++) {
      out[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    xor_32(a, b, out);
    free(a);
    free(b);
    free(out);

    break;
  }
  case 2: {

    int _len_a0 = 10000;
    int *a = (int *)malloc(_len_a0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_a0; _i0++) {
      a[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b0 = 10000;
    int *b = (int *)malloc(_len_b0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b0; _i0++) {
      b[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_out0 = 10000;
    int *out = (int *)malloc(_len_out0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_out0; _i0++) {
      out[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    xor_32(a, b, out);
    free(a);
    free(b);
    free(out);

    break;
  }
  case 3: {

    int _len_a0 = 22500;
    int *a = (int *)malloc(_len_a0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_a0; _i0++) {
      a[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b0 = 22500;
    int *b = (int *)malloc(_len_b0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b0; _i0++) {
      b[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_out0 = 22500;
    int *out = (int *)malloc(_len_out0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_out0; _i0++) {
      out[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    xor_32(a, b, out);
    free(a);
    free(b);
    free(out);

    break;
  }
  case 4: {

    int _len_a0 = 40000;
    int *a = (int *)malloc(_len_a0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_a0; _i0++) {
      a[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b0 = 40000;
    int *b = (int *)malloc(_len_b0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b0; _i0++) {
      b[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_out0 = 40000;
    int *out = (int *)malloc(_len_out0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_out0; _i0++) {
      out[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    xor_32(a, b, out);
    free(a);
    free(b);
    free(out);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
