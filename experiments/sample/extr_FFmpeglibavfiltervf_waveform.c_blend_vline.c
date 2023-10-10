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
typedef float uint8_t;

/* Variables and functions */

__attribute__((used)) static void blend_vline(uint8_t *dst, int height,
                                              int linesize, float o1, float o2,
                                              int v, int step, int dst_size) {
  unsigned counterblend_vline0 = 0;

  int tempstep = step;
  int tempheight = height;

  int y;

  for (y = 0; y < height; y += step) {
    counterblend_vline0++;
    dst[0] = v * o1 + dst[0] * o2;

    dst += linesize * step;
  }

  printf("1\n");
  printf("at line 62 :");
  printf(" step height dst_size\n");
  printf("%d %d %d %d\n", tempstep, tempheight, dst_size, counterblend_vline0);
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
    int height = 10;
    int linesize = 10;
    float o1 =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    float o2 =
        ((-2.0 * (next_i() % 2)) + 1.0) *
        (-16777216.000000 +
         (float)next_f() /
             (((float)16777215.000000 / (16777215.000000 - -16777216.000000))));
    int v = 10;
    int step = 10;
    int _len_dst0 = 100;
    float *dst = (float *)malloc(_len_dst0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_dst0; _i0++) {
      dst[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
                 (-16777216.000000 +
                  (float)next_f() / (((float)16777215.000000 /
                                      (16777215.000000 - -16777216.000000))));
    }
    blend_vline(dst, height, linesize, o1, o2, v, step, _len_dst0);
    free(dst);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
