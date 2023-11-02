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
int ENOENT;

__attribute__((used)) static int int3406_thermal_get_index(int *array, int nr,
                                                           int value) {
  unsigned counterint3406_thermal_get_index0 = 0;

  int tempnr = nr;

  int i;

  for (i = 2; i < nr; i++) {
    counterint3406_thermal_get_index0++;
    if (array[i] == value) {
      break;
    }
  }

  printf("Maximum nesting depth: 1\n");
  printf("Number of loops: 1\n");
  printf("at line 63 :");
  printf(" nr\n");
  printf("%d %d\n", tempnr, counterint3406_thermal_get_index0);
  return i == nr ? -ENOENT : i;
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
    int nr = 255;

    int value = 255;

    int _len_array0 = 65025;
    int *array = (int *)malloc(_len_array0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_array0; _i0++) {
      array[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int benchRet = int3406_thermal_get_index(array, nr, value);

    free(array);

    break;
  }
  // big-arr-10x
  case 1: {
    int nr = 10;

    int value = 10;

    int _len_array0 = 100;
    int *array = (int *)malloc(_len_array0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_array0; _i0++) {
      array[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int benchRet = int3406_thermal_get_index(array, nr, value);

    free(array);

    break;
  }
  case 2: {
    int nr = 100;

    int value = 100;

    int _len_array0 = 10000;
    int *array = (int *)malloc(_len_array0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_array0; _i0++) {
      array[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int benchRet = int3406_thermal_get_index(array, nr, value);

    free(array);

    break;
  }
  case 3: {
    int nr = 150;

    int value = 150;

    int _len_array0 = 22500;
    int *array = (int *)malloc(_len_array0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_array0; _i0++) {
      array[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int benchRet = int3406_thermal_get_index(array, nr, value);

    free(array);

    break;
  }
  case 4: {
    int nr = 200;

    int value = 200;

    int _len_array0 = 40000;
    int *array = (int *)malloc(_len_array0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_array0; _i0++) {
      array[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int benchRet = int3406_thermal_get_index(array, nr, value);

    free(array);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
