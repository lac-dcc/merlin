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

void const_cpu(int N, float ALPHA, float *X, int INCX) {
  unsigned counterconst_cpu0 = 0;

  int tempN = N;

  int i;
  for (i = 0; i < N; ++i) {
    counterconst_cpu0++;
    X[i * INCX] = ALPHA;
  }

  printf("Number of counters: 1\n");
  printf("At line 58 :");
  printf(" N\n");
  printf("Nesting depth: 1\n");
  printf("%d %d\n", tempN, counterconst_cpu0);
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
    int N = 10;
    float ALPHA =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    int INCX = 10;
    int _len_X0 = 100;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }
    const_cpu(N, ALPHA, X, INCX);
    free(X);

    break;
  }
  case 1: {
    int N = 100;
    float ALPHA =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    int INCX = 100;
    int _len_X0 = 10000;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }
    const_cpu(N, ALPHA, X, INCX);
    free(X);

    break;
  }
  case 2: {
    int N = 255;
    float ALPHA =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    int INCX = 255;
    int _len_X0 = 65025;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }
    const_cpu(N, ALPHA, X, INCX);
    free(X);

    break;
  }
  case 3: {
    int N = 150;
    float ALPHA =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    int INCX = 150;
    int _len_X0 = 22500;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }
    const_cpu(N, ALPHA, X, INCX);
    free(X);

    break;
  }
  case 4: {
    int N = 200;
    float ALPHA =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    int INCX = 200;
    int _len_X0 = 40000;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }
    const_cpu(N, ALPHA, X, INCX);
    free(X);

    break;
  }
  default:
    usage();
    break;
  }

  return 0;
}
