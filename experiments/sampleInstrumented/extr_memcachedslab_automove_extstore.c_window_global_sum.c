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
typedef int uint32_t;
struct window_global {
  scalar_t__ pool_low;
  scalar_t__ pool_high;
};

/* Variables and functions */

__attribute__((used)) static void window_global_sum(struct window_global *wg,
                                                    struct window_global *w,
                                                    uint32_t size) {
  unsigned counterwindow_global_sum0 = 0;

  uint32_t tempsize = size;

  for (int x = 0; x < size; x++) {
    counterwindow_global_sum0++;
    struct window_global *d = &wg[x];
    w->pool_high += d->pool_high;
    w->pool_low += d->pool_low;
  }

  printf("Number of counters: 1\n");
  printf("At line 66 :");
  printf(" size\n");
  printf("Nesting depth: 1\n");
  printf("%d %d\n", tempsize, counterwindow_global_sum0);
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
    // static_instructions_O0 : 30
    // dynamic_instructions_O0 : 5621
    // -------------------------------
    // static_instructions_O1 : 16
    // dynamic_instructions_O1 : 1794
    // -------------------------------
    // static_instructions_O2 : 46
    // dynamic_instructions_O2 : 1050
    // -------------------------------
    // static_instructions_O3 : 46
    // dynamic_instructions_O3 : 1050
    // -------------------------------
    // static_instructions_Ofast : 46
    // dynamic_instructions_Ofast : 1050
    // -------------------------------
    // static_instructions_Os : 16
    // dynamic_instructions_Os : 1540
    // -------------------------------
    // static_instructions_Oz : 16
    // dynamic_instructions_Oz : 2050
    // -------------------------------

    int size = 255;

    int _len_wg0 = 65025;
    struct window_global *wg =
        (struct window_global *)malloc(_len_wg0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_wg0; _i0++) {
      wg[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      wg[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_w0 = 65025;
    struct window_global *w =
        (struct window_global *)malloc(_len_w0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_w0; _i0++) {
      w[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      w[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    window_global_sum(wg, w, size);
    free(wg);
    free(w);

    break;
  }

  // big-arr-10x
  case 1: {
    int size = 10;

    int _len_wg0 = 100;
    struct window_global *wg =
        (struct window_global *)malloc(_len_wg0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_wg0; _i0++) {
      wg[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      wg[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_w0 = 100;
    struct window_global *w =
        (struct window_global *)malloc(_len_w0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_w0; _i0++) {
      w[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      w[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    window_global_sum(wg, w, size);
    free(wg);
    free(w);

    break;
  }
  case 2: {
    int size = 100;

    int _len_wg0 = 10000;
    struct window_global *wg =
        (struct window_global *)malloc(_len_wg0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_wg0; _i0++) {
      wg[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      wg[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_w0 = 10000;
    struct window_global *w =
        (struct window_global *)malloc(_len_w0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_w0; _i0++) {
      w[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      w[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    window_global_sum(wg, w, size);
    free(wg);
    free(w);

    break;
  }
  case 3: {
    int size = 150;

    int _len_wg0 = 22500;
    struct window_global *wg =
        (struct window_global *)malloc(_len_wg0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_wg0; _i0++) {
      wg[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      wg[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_w0 = 22500;
    struct window_global *w =
        (struct window_global *)malloc(_len_w0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_w0; _i0++) {
      w[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      w[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    window_global_sum(wg, w, size);
    free(wg);
    free(w);

    break;
  }
  case 4: {
    int size = 200;

    int _len_wg0 = 40000;
    struct window_global *wg =
        (struct window_global *)malloc(_len_wg0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_wg0; _i0++) {
      wg[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      wg[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_w0 = 40000;
    struct window_global *w =
        (struct window_global *)malloc(_len_w0 * sizeof(struct window_global));
    for (int _i0 = 0; _i0 < _len_w0; _i0++) {
      w[_i0].pool_low = ((-2 * (next_i() % 2)) + 1) * next_i();
      w[_i0].pool_high = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    window_global_sum(wg, w, size);
    free(wg);
    free(w);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
