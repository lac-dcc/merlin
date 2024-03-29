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
typedef int /*<<< orphan*/ uint8_t;
typedef int ptrdiff_t;

/* Variables and functions */

__attribute__((used)) static inline void
transpose_block_8_c(uint8_t *src, ptrdiff_t src_linesize, uint8_t *dst,
                    ptrdiff_t dst_linesize, int w, int h) {
  unsigned countertranspose_block_8_c1 = 0;
  unsigned countertranspose_block_8_c0 = 0;

  int tempw = w;
  int temph = h;

  int x, y;
  for (y = 0; y < h; y++, dst += dst_linesize, src++) {
    countertranspose_block_8_c0++;
    for (x = 0; x < w; x++) {
      countertranspose_block_8_c1++;
      dst[x] = src[x * src_linesize];
    }
  }

  printf("Number of counters: 2\n");
  printf("At line 65 :");
  printf(" w h\n");
  printf("Nesting depth: 2\n");
  printf("At line 64 :");
  printf(" h\n");
  printf("Nesting depth: 1\n");
  printf("%d %d %d\n", tempw, temph, countertranspose_block_8_c1);
  printf("%d %d\n", temph, countertranspose_block_8_c0);
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
    // static_instructions_O0 : 44
    // dynamic_instructions_O0 : 980744
    // -------------------------------
    // static_instructions_O1 : 34
    // dynamic_instructions_O1 : 392972
    // -------------------------------
    // static_instructions_O2 : 120
    // dynamic_instructions_O2 : 207124
    // -------------------------------
    // static_instructions_O3 : 117
    // dynamic_instructions_O3 : 205851
    // -------------------------------
    // static_instructions_Ofast : 117
    // dynamic_instructions_Ofast : 205851
    // -------------------------------
    // static_instructions_Os : 31
    // dynamic_instructions_Os : 392461
    // -------------------------------
    // static_instructions_Oz : 30
    // dynamic_instructions_Oz : 457742
    // -------------------------------

    int src_linesize = 255;

    int dst_linesize = 255;

    int w = 255;

    int h = 255;

    int _len_src0 = 65025;
    int *src = (int *)malloc(_len_src0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_src0; _i0++) {
      src[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_dst0 = 65025;
    int *dst = (int *)malloc(_len_dst0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dst0; _i0++) {
      dst[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    transpose_block_8_c(src, src_linesize, dst, dst_linesize, w, h);
    free(src);
    free(dst);

    break;
  }

  // big-arr-10x
  case 1: {
    int src_linesize = 10;

    int dst_linesize = 10;

    int w = 10;

    int h = 10;

    int _len_src0 = 100;
    int *src = (int *)malloc(_len_src0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_src0; _i0++) {
      src[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_dst0 = 100;
    int *dst = (int *)malloc(_len_dst0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dst0; _i0++) {
      dst[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    transpose_block_8_c(src, src_linesize, dst, dst_linesize, w, h);
    free(src);
    free(dst);

    break;
  }
  case 2: {
    int src_linesize = 100;

    int dst_linesize = 100;

    int w = 100;

    int h = 100;

    int _len_src0 = 10000;
    int *src = (int *)malloc(_len_src0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_src0; _i0++) {
      src[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_dst0 = 10000;
    int *dst = (int *)malloc(_len_dst0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dst0; _i0++) {
      dst[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    transpose_block_8_c(src, src_linesize, dst, dst_linesize, w, h);
    free(src);
    free(dst);

    break;
  }
  case 3: {
    int src_linesize = 150;

    int dst_linesize = 150;

    int w = 150;

    int h = 150;

    int _len_src0 = 22500;
    int *src = (int *)malloc(_len_src0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_src0; _i0++) {
      src[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_dst0 = 22500;
    int *dst = (int *)malloc(_len_dst0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dst0; _i0++) {
      dst[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    transpose_block_8_c(src, src_linesize, dst, dst_linesize, w, h);
    free(src);
    free(dst);

    break;
  }
  case 4: {
    int src_linesize = 200;

    int dst_linesize = 200;

    int w = 200;

    int h = 200;

    int _len_src0 = 40000;
    int *src = (int *)malloc(_len_src0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_src0; _i0++) {
      src[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_dst0 = 40000;
    int *dst = (int *)malloc(_len_dst0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_dst0; _i0++) {
      dst[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    transpose_block_8_c(src, src_linesize, dst, dst_linesize, w, h);
    free(src);
    free(dst);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
