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
typedef int uint8_t;

/* Variables and functions */

__attribute__((used)) static void mv_test(uint8_t *dst, int dst_linesize,
                                          int off) {
  unsigned countermv_test1 = 0;
  unsigned countermv_test0 = 0;

  int x, y;

  for (y = 0; y < 16 * 16; y++) {
    countermv_test0++;
    if (y & 16) {
      continue;
    }
    for (x = 0; x < 16 * 16; x++) {
      countermv_test1++;
      dst[x + y * dst_linesize] = x + off * 8 / (y / 32 + 1);
    }
  }

  printf("2\n");
  printf("at line 65 :");
  printf("\n");
  printf("at line 61 :");
  printf("\n");
  printf("%d\n", countermv_test1);
  printf("%d\n", countermv_test0);
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
    // static_instructions_O0 : 50
    // dynamic_instructions_O0 : 953482
    // -------------------------------
    // static_instructions_O1 : 31
    // dynamic_instructions_O1 : 166666
    // -------------------------------
    // static_instructions_O2 : 53
    // dynamic_instructions_O2 : 38414
    // -------------------------------
    // static_instructions_O3 : 53
    // dynamic_instructions_O3 : 38414
    // -------------------------------
    // static_instructions_Ofast : 53
    // dynamic_instructions_Ofast : 38414
    // -------------------------------
    // static_instructions_Os : 34
    // dynamic_instructions_Os : 60171
    // -------------------------------
    // static_instructions_Oz : 29
    // dynamic_instructions_Oz : 199563
    // -------------------------------

    int dst_linesize = 255;

    int off = 255;

    int _len_dst0 = 65025;
    int *dst = (int *)malloc(_len_dst0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dst0; _i0++) {
      dst[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    mv_test(dst, dst_linesize, off);
    free(dst);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
