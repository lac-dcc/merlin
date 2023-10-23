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
typedef size_t u8;
typedef size_t u32;

/* Variables and functions */

__attribute__((used)) static u8 msdc_dma_calcs(u8 *buf, u32 len) {
  unsigned countermsdc_dma_calcs0 = 0;

  u32 templen = len;

  u32 i, sum = 0;

  for (i = 0; i < len; i++) {
    countermsdc_dma_calcs0++;
    sum += buf[i];
  }

  printf("1\n");
  printf("at line 61 :");
  printf(" len\n");
  printf("%ld %d\n", templen, countermsdc_dma_calcs0);
  return 0xff - (u8)sum;
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
    unsigned long len = 10;
    int _len_buf0 = 100;
    unsigned long *buf =
        (unsigned long *)malloc(_len_buf0 * sizeof(unsigned long));
    for (int _i0 = 0; _i0 < _len_buf0; _i0++) {
      buf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    unsigned long benchRet = msdc_dma_calcs(buf, len);
    free(buf);

    break;
  }
  case 1: {
    unsigned long len = 100;
    int _len_buf0 = 10000;
    unsigned long *buf =
        (unsigned long *)malloc(_len_buf0 * sizeof(unsigned long));
    for (int _i0 = 0; _i0 < _len_buf0; _i0++) {
      buf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    unsigned long benchRet = msdc_dma_calcs(buf, len);
    free(buf);

    break;
  }
  case 2: {
    unsigned long len = 255;
    int _len_buf0 = 65025;
    unsigned long *buf =
        (unsigned long *)malloc(_len_buf0 * sizeof(unsigned long));
    for (int _i0 = 0; _i0 < _len_buf0; _i0++) {
      buf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    unsigned long benchRet = msdc_dma_calcs(buf, len);
    free(buf);

    break;
  }
  case 3: {
    unsigned long len = 150;
    int _len_buf0 = 22500;
    unsigned long *buf =
        (unsigned long *)malloc(_len_buf0 * sizeof(unsigned long));
    for (int _i0 = 0; _i0 < _len_buf0; _i0++) {
      buf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    unsigned long benchRet = msdc_dma_calcs(buf, len);
    free(buf);

    break;
  }
  case 4: {
    unsigned long len = 200;
    int _len_buf0 = 40000;
    unsigned long *buf =
        (unsigned long *)malloc(_len_buf0 * sizeof(unsigned long));
    for (int _i0 = 0; _i0 < _len_buf0; _i0++) {
      buf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    unsigned long benchRet = msdc_dma_calcs(buf, len);
    free(buf);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
