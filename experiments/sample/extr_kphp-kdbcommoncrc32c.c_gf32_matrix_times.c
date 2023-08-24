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

__attribute__((used)) static unsigned gf32_matrix_times(unsigned *matrix,
                                                        unsigned vector) {
  unsigned countergf32_matrix_times0 = 0;

  unsigned sum = 0;
  while (vector) {
    countergf32_matrix_times0++;
    if (vector & 1) {
      sum ^= *matrix;
    }
    vector >>= 1;
    matrix++;
  }

  printf("1\n");
  printf("at line 59 :");
  printf("\n");
  printf("%d\n", countergf32_matrix_times0);
  return sum;
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
    unsigned int vector = 10;
    int _len_matrix0 = 100;
    unsigned int *matrix =
        (unsigned int *)malloc(_len_matrix0 * sizeof(unsigned int));
    for (int _i0 = 0; _i0 < _len_matrix0; _i0++) {
      matrix[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    unsigned int benchRet = gf32_matrix_times(matrix, vector);
    printf("%u\n", benchRet);
    free(matrix);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
