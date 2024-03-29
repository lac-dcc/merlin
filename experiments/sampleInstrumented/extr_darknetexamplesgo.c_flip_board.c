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

void flip_board(float *board) {
  unsigned counterflip_board0 = 0;

  int i;
  for (i = 0; i < 19 * 19; ++i) {
    counterflip_board0++;
    float swap = board[i];
    board[i] = board[i + 19 * 19];
    board[i + 19 * 19] = swap;
    board[i + 19 * 19 * 2] = 1 - board[i + 19 * 19 * 2];
  }

  printf("Number of counters: 1\n");
  printf("At line 58 :");
  printf("\n");
  printf("Nesting depth: 0\n");
  printf("%d\n", counterflip_board0);
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
    int _len_board0 = 65025;
    float *board = (float *)malloc(_len_board0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_board0; _i0++) {
      board[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
                   (-16777216.000000 +
                    (float)next_f() / (((float)16777215.000000 /
                                        (16777215.000000 - -16777216.000000))));
    }

    flip_board(board);
    free(board);

    break;
  }
  case 1: {
    int _len_board0 = 10000;
    float *board = (float *)malloc(_len_board0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_board0; _i0++) {
      board[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
                   (-16777216.000000 +
                    (float)next_f() / (((float)16777215.000000 /
                                        (16777215.000000 - -16777216.000000))));
    }

    flip_board(board);
    free(board);

    break;
  }
  case 2: {
    int _len_board0 = 100;
    float *board = (float *)malloc(_len_board0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_board0; _i0++) {
      board[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
                   (-16777216.000000 +
                    (float)next_f() / (((float)16777215.000000 /
                                        (16777215.000000 - -16777216.000000))));
    }

    flip_board(board);
    free(board);

    break;
  }
  case 3: {
    int _len_board0 = 22500;
    float *board = (float *)malloc(_len_board0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_board0; _i0++) {
      board[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
                   (-16777216.000000 +
                    (float)next_f() / (((float)16777215.000000 /
                                        (16777215.000000 - -16777216.000000))));
    }

    flip_board(board);
    free(board);

    break;
  }
  case 4: {
    int _len_board0 = 40000;
    float *board = (float *)malloc(_len_board0 * sizeof(float));
    for (int _i0 = 0; _i0 < _len_board0; _i0++) {
      board[_i0] = ((-2.0 * (next_i() % 2)) + 1.0) *
                   (-16777216.000000 +
                    (float)next_f() / (((float)16777215.000000 /
                                        (16777215.000000 - -16777216.000000))));
    }

    flip_board(board);
    free(board);

    break;
  }
  default:
    usage();
    break;
  }

  return 0;
}
