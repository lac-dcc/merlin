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
typedef int u8;

/* Variables and functions */

__attribute__((used)) static u8 vp702x_chksum(u8 *buf, int f, int count) {
  unsigned countervp702x_chksum0 = 0;

  int tempf = f;
  int tempcount = count;

  u8 s = 0;
  int i;
  for (i = f; i < f + count; i++) {
    countervp702x_chksum0++;
    s += buf[i];
  }

  printf("1\n");
  printf("at line 60 :");
  printf(" f count\n");
  printf("%d %d %d\n", tempf, tempcount, countervp702x_chksum0);
  return ~s + 1;
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
    int f = 10;
    int count = 10;
    int _len_buf0 = 100;
    int *buf = (int *)malloc(_len_buf0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_buf0; _i0++) {
      buf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = vp702x_chksum(buf, f, count);
    printf("%d\n", benchRet);
    free(buf);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}