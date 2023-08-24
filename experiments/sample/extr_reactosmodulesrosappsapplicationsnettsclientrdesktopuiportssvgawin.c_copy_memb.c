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
typedef int /*<<< orphan*/ uint8;

/* Variables and functions */

void copy_memb(uint8 *d, uint8 *s, int n) {
  unsigned countercopy_memb0 = 0;
  unsigned countercopy_memb1 = 0;

  int tempn = n;

  d = (d + n) - 1;
  s = (s + n) - 1;
  while (n & (~7)) {
    countercopy_memb0++;
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    n = n - 8;
  }
  while (n > 0) {
    countercopy_memb1++;
    *(d--) = *(s--);
    n--;
  }

  printf("2\n");
  printf("at line 61 :");
  printf(" n\n");
  printf("at line 72 :");
  printf(" n\n");
  printf("%d %d\n", tempn, countercopy_memb0);
  printf("%d %d\n", tempn, countercopy_memb1);
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
    // static_instructions_O0 : 124
    // dynamic_instructions_O0 : 2866
    // -------------------------------
    // static_instructions_O1 : 44
    // dynamic_instructions_O1 : 710
    // -------------------------------
    // static_instructions_O2 : 47
    // dynamic_instructions_O2 : 713
    // -------------------------------
    // static_instructions_O3 : 47
    // dynamic_instructions_O3 : 713
    // -------------------------------
    // static_instructions_Ofast : 47
    // dynamic_instructions_Ofast : 713
    // -------------------------------
    // static_instructions_Os : 42
    // dynamic_instructions_Os : 708
    // -------------------------------
    // static_instructions_Oz : 39
    // dynamic_instructions_Oz : 745
    // -------------------------------

    int n = 255;

    int _len_d0 = 65025;
    int *d = (int *)malloc(_len_d0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_d0; _i0++) {
      d[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_s0 = 65025;
    int *s = (int *)malloc(_len_s0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    copy_memb(d, s, n);
    free(d);
    free(s);

    break;
  }

  // big-arr-10x
  case 1: {
    // static_instructions_O0 : 124
    // dynamic_instructions_O0 : 146
    // -------------------------------
    // static_instructions_O1 : 44
    // dynamic_instructions_O1 : 50
    // -------------------------------
    // static_instructions_O2 : 47
    // dynamic_instructions_O2 : 53
    // -------------------------------
    // static_instructions_O3 : 47
    // dynamic_instructions_O3 : 53
    // -------------------------------
    // static_instructions_Ofast : 47
    // dynamic_instructions_Ofast : 53
    // -------------------------------
    // static_instructions_Os : 42
    // dynamic_instructions_Os : 48
    // -------------------------------
    // static_instructions_Oz : 39
    // dynamic_instructions_Oz : 50
    // -------------------------------

    int n = 10;

    int _len_d0 = 100;
    int *d = (int *)malloc(_len_d0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_d0; _i0++) {
      d[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_s0 = 100;
    int *s = (int *)malloc(_len_s0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    copy_memb(d, s, n);
    free(d);
    free(s);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
