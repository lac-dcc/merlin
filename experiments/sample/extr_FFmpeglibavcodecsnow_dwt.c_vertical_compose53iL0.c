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
typedef int IDWTELEM;

/* Variables and functions */

__attribute__((used)) static void
vertical_compose53iL0(IDWTELEM *b0, IDWTELEM *b1, IDWTELEM *b2, int width) {
  unsigned countervertical_compose53iL00 = 0;

  int tempwidth = width;

  int i;

  for (i = 0; i < width; i++) {
    countervertical_compose53iL00++;
    b1[i] -= (b0[i] + b2[i] + 2) >> 2;
  }

  printf("1\n");
  printf("at line 63 :");
  printf(" width\n");
  printf("%d %d\n", tempwidth, countervertical_compose53iL00);
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
    // static_instructions_O0 : 29
    // dynamic_instructions_O0 : 5112
    // -------------------------------
    // static_instructions_O1 : 18
    // dynamic_instructions_O1 : 2304
    // -------------------------------
    // static_instructions_O2 : 81
    // dynamic_instructions_O2 : 681
    // -------------------------------
    // static_instructions_O3 : 81
    // dynamic_instructions_O3 : 681
    // -------------------------------
    // static_instructions_Ofast : 81
    // dynamic_instructions_Ofast : 681
    // -------------------------------
    // static_instructions_Os : 17
    // dynamic_instructions_Os : 2303
    // -------------------------------
    // static_instructions_Oz : 17
    // dynamic_instructions_Oz : 2559
    // -------------------------------

    int width = 255;

    int _len_b00 = 65025;
    int *b0 = (int *)malloc(_len_b00 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b00; _i0++) {
      b0[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b10 = 65025;
    int *b1 = (int *)malloc(_len_b10 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b10; _i0++) {
      b1[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b20 = 65025;
    int *b2 = (int *)malloc(_len_b20 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b20; _i0++) {
      b2[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    vertical_compose53iL0(b0, b1, b2, width);
    free(b0);
    free(b1);
    free(b2);

    break;
  }

  // big-arr-10x
  case 1: {
    // static_instructions_O0 : 29
    // dynamic_instructions_O0 : 212
    // -------------------------------
    // static_instructions_O1 : 18
    // dynamic_instructions_O1 : 99
    // -------------------------------
    // static_instructions_O2 : 74
    // dynamic_instructions_O2 : 74
    // -------------------------------
    // static_instructions_O3 : 74
    // dynamic_instructions_O3 : 74
    // -------------------------------
    // static_instructions_Ofast : 74
    // dynamic_instructions_Ofast : 74
    // -------------------------------
    // static_instructions_Os : 17
    // dynamic_instructions_Os : 98
    // -------------------------------
    // static_instructions_Oz : 17
    // dynamic_instructions_Oz : 109
    // -------------------------------

    int width = 10;

    int _len_b00 = 100;
    int *b0 = (int *)malloc(_len_b00 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b00; _i0++) {
      b0[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b10 = 100;
    int *b1 = (int *)malloc(_len_b10 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b10; _i0++) {
      b1[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b20 = 100;
    int *b2 = (int *)malloc(_len_b20 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b20; _i0++) {
      b2[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    vertical_compose53iL0(b0, b1, b2, width);
    free(b0);
    free(b1);
    free(b2);

    break;
  }

  // empty
  case 2: {
    // static_instructions_O0 : 12
    // dynamic_instructions_O0 : 12
    // -------------------------------
    // static_instructions_O1 : 6
    // dynamic_instructions_O1 : 6
    // -------------------------------
    // static_instructions_O2 : 6
    // dynamic_instructions_O2 : 6
    // -------------------------------
    // static_instructions_O3 : 6
    // dynamic_instructions_O3 : 6
    // -------------------------------
    // static_instructions_Ofast : 6
    // dynamic_instructions_Ofast : 6
    // -------------------------------
    // static_instructions_Os : 6
    // dynamic_instructions_Os : 6
    // -------------------------------
    // static_instructions_Oz : 9
    // dynamic_instructions_Oz : 9
    // -------------------------------

    int width = ((-2 * (next_i() % 2)) + 1) * next_i();

    int _len_b00 = 1;
    int *b0 = (int *)malloc(_len_b00 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b00; _i0++) {
      b0[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b10 = 1;
    int *b1 = (int *)malloc(_len_b10 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b10; _i0++) {
      b1[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_b20 = 1;
    int *b2 = (int *)malloc(_len_b20 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_b20; _i0++) {
      b2[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    vertical_compose53iL0(b0, b1, b2, width);
    free(b0);
    free(b1);
    free(b2);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
