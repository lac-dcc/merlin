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

/* Variables and functions */

float dot_cpu(int N, float *X, int INCX, float *Y, int INCY) {
  unsigned counterdot_cpu0 = 0;

  int tempN = N;

  int i;
  float dot = 0;
  for (i = 0; i < N; ++i) {
    counterdot_cpu0++;
    dot += X[i * INCX] * Y[i * INCY];
  }

  printf("1\n");
  printf("at line 61 :");
  printf(" N\n");
  printf("%d %d\n", tempN, counterdot_cpu0);
  return dot;
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
    int N = 255;

    int INCX = 255;

    int INCY = 255;

    int _len_X0 = 65025;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }

    int _len_Y0 = 65025;
    float *Y = (float *)malloc(_len_Y0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_Y0; _i0++) {
      Y[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }

    float benchRet = dot_cpu(N, X, INCX, Y, INCY);
    printf("%f\n", benchRet);
    free(X);
    free(Y);

    break;
  }
  // big-arr-10x
  case 1: {
    int N = 10;

    int INCX = 10;

    int INCY = 10;

    int _len_X0 = 100;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }

    int _len_Y0 = 100;
    float *Y = (float *)malloc(_len_Y0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_Y0; _i0++) {
      Y[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }

    float benchRet = dot_cpu(N, X, INCX, Y, INCY);
    printf("%f\n", benchRet);
    free(X);
    free(Y);

    break;
  }
  // empty
  case 2: {
    int N = ((-2 * (next_i() % 2)) + 1) * next_i();

    int INCX = ((-2 * (next_i() % 2)) + 1) * next_i();

    int INCY = ((-2 * (next_i() % 2)) + 1) * next_i();

    int _len_X0 = 1;
    float *X = (float *)malloc(_len_X0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_X0; _i0++) {
      X[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }

    int _len_Y0 = 1;
    float *Y = (float *)malloc(_len_Y0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_Y0; _i0++) {
      Y[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
               (-16777216.000000 +
                (float)next_f() / (((float)16777215.000000 /
                                    (16777215.000000 - -16777216.000000))));
    }

    float benchRet = dot_cpu(N, X, INCX, Y, INCY);
    printf("%f\n", benchRet);
    free(X);
    free(Y);

    break;
  }
  default:
    usage();
    break;
  }

  return 0;
}