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

__attribute__((used)) static bool is_duplicate_irq(int irq, int *irqs,
                                                   int nr_irqs) {
  unsigned counteris_duplicate_irq0 = 0;

  int tempnr_irqs = nr_irqs;

  int i;

  for (i = 0; i < nr_irqs; i++) {
    counteris_duplicate_irq0++;
    if (irq == irqs[i]) {

      printf("Number of counters: 1\n");
      printf("At line 60 :");
      printf(" nr_irqs\n");
      printf("Nesting depth: 1\n");
      printf("%d %d\n", tempnr_irqs, counteris_duplicate_irq0);
      return true;
    }
  }

  printf("Number of counters: 1\n");
  printf("At line 60 :");
  printf(" nr_irqs\n");
  printf("Nesting depth: 1\n");
  printf("%d %d\n", tempnr_irqs, counteris_duplicate_irq0);
  return false;
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
    int irq = 10;
    int nr_irqs = 10;
    int _len_irqs0 = 100;
    int *irqs = (int *)malloc(_len_irqs0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_irqs0; _i0++) {
      irqs[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = is_duplicate_irq(irq, irqs, nr_irqs);
    free(irqs);

    break;
  }
  case 1: {
    int irq = 100;
    int nr_irqs = 100;
    int _len_irqs0 = 10000;
    int *irqs = (int *)malloc(_len_irqs0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_irqs0; _i0++) {
      irqs[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = is_duplicate_irq(irq, irqs, nr_irqs);
    free(irqs);

    break;
  }
  case 2: {
    int irq = 150;
    int nr_irqs = 150;
    int _len_irqs0 = 22500;
    int *irqs = (int *)malloc(_len_irqs0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_irqs0; _i0++) {
      irqs[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = is_duplicate_irq(irq, irqs, nr_irqs);
    free(irqs);

    break;
  }
  case 3: {
    int irq = 255;
    int nr_irqs = 255;
    int _len_irqs0 = 65025;
    int *irqs = (int *)malloc(_len_irqs0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_irqs0; _i0++) {
      irqs[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = is_duplicate_irq(irq, irqs, nr_irqs);
    free(irqs);

    break;
  }
  case 4: {
    int irq = 200;
    int nr_irqs = 200;
    int _len_irqs0 = 40000;
    int *irqs = (int *)malloc(_len_irqs0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_irqs0; _i0++) {
      irqs[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = is_duplicate_irq(irq, irqs, nr_irqs);
    free(irqs);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
