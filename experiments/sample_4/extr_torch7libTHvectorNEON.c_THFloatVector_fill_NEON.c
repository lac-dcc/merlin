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
typedef int ptrdiff_t;

/* Variables and functions */

__attribute__((used)) static void
THFloatVector_fill_NEON(float *x, const float c, const ptrdiff_t n) {
  unsigned counterTHFloatVector_fill_NEON0 = 0;
  unsigned counterTHFloatVector_fill_NEON1 = 0;

  const ptrdiff_t tempn = n;

  long i = 0;

  for (; i < n - 4; i += 4) {
    counterTHFloatVector_fill_NEON0++;
    x[i] = c;
    x[i + 1] = c;
    x[i + 2] = c;
    x[i + 3] = c;
  }

  for (; i < n; i++) {
    counterTHFloatVector_fill_NEON1++;
    x[i] = c;
  }

  printf("2\n");
  printf("at line 61 :");
  printf(" n\n");
  printf("at line 68 :");
  printf(" n\n");
  printf(" %d\n", tempn, counterTHFloatVector_fill_NEON0);
  printf(" %d\n", tempn, counterTHFloatVector_fill_NEON1);
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
    const float c =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    const int n = 10;
    int _len_x0 = 100;
    float *x = (float *)malloc(_len_x0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_x0; _i0++) {
      x[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }
    THFloatVector_fill_NEON(x, c, n);
    free(x);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
