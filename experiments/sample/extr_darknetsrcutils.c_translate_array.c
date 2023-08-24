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

/* Variables and functions */

void translate_array(float *a, int n, float s) {
  unsigned countertranslate_array0 = 0;

  int tempn = n;

  int i;
  for (i = 0; i < n; ++i) {
    countertranslate_array0++;
    a[i] += s;
  }

  printf("1\n");
  printf("at line 58 :");
  printf(" n\n");
  printf("%d %d\n", tempn, countertranslate_array0);
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
    int n = 10;
    float s =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    int _len_a0 = 100;
    float *a = (float *)malloc(_len_a0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_a0; _i0++) {
      a[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }
    translate_array(a, n, s);
    free(a);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
