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
       0            int-bounds\n\
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
typedef int /*<<< orphan*/ u8b;

/* Variables and functions */

int maccpy(u8b dest[16], u8b source[16]) {
  unsigned countermaccpy0 = 0;

  int i;
  for (i = 0; i < 16; i++) {
    countermaccpy0++;
    dest[i] = source[i];
  }

  printf("Maximum nesting depth: 1\n");
  printf("Number of loops: 1\n");
  printf("at line 59 :");
  printf("\n");
  printf("%d\n", countermaccpy0);
  return 0;
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

  // int-bounds
  case 0: {
    int _len_dest0 = 100;
    int *dest = (int *)malloc(_len_dest0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dest0; _i0++) {
      dest[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int _len_source0 = 100;
    int *source = (int *)malloc(_len_source0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_source0; _i0++) {
      source[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = maccpy(dest, source);
    free(dest);
    free(source);
    break;
  }
  case 1: {
    int _len_dest0 = 10000;
    int *dest = (int *)malloc(_len_dest0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dest0; _i0++) {
      dest[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int _len_source0 = 10000;
    int *source = (int *)malloc(_len_source0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_source0; _i0++) {
      source[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = maccpy(dest, source);
    free(dest);
    free(source);
    break;
  }
  case 2: {
    int _len_dest0 = 65025;
    int *dest = (int *)malloc(_len_dest0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dest0; _i0++) {
      dest[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int _len_source0 = 65025;
    int *source = (int *)malloc(_len_source0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_source0; _i0++) {
      source[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = maccpy(dest, source);
    free(dest);
    free(source);
    break;
  }
  case 3: {
    int _len_dest0 = 22500;
    int *dest = (int *)malloc(_len_dest0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dest0; _i0++) {
      dest[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int _len_source0 = 22500;
    int *source = (int *)malloc(_len_source0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_source0; _i0++) {
      source[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = maccpy(dest, source);
    free(dest);
    free(source);
    break;
  }
  case 4: {
    int _len_dest0 = 40000;
    int *dest = (int *)malloc(_len_dest0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dest0; _i0++) {
      dest[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int _len_source0 = 40000;
    int *source = (int *)malloc(_len_source0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_source0; _i0++) {
      source[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = maccpy(dest, source);
    free(dest);
    free(source);
    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
