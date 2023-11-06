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
       0            int-bounds\n\
       1            big-arr\n\
       2            big-arr-10x\n\
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
typedef unsigned int uint32_t;

/* Variables and functions */
int CCV_CLI_NONE;

int ccv_cli_output_level_and_above(int level) {
  unsigned counterccv_cli_output_level_and_above0 = 0;

  if (level == CCV_CLI_NONE) {

    printf("Number of counters: 1\n");
    printf("At line 66 :");
    printf("\n");
    printf("Nesting depth: 1\n");
    printf("%d\n", counterccv_cli_output_level_and_above0);
    return CCV_CLI_NONE;
  }
  int i;
  uint32_t levels = 0;
  for (i = 0; i < 32; i++) {
    counterccv_cli_output_level_and_above0++;
    if (level <= (1u << i)) {
      levels |= 1u << i;
    }
  }

  printf("Number of counters: 1\n");
  printf("At line 66 :");
  printf("\n");
  printf("Nesting depth: 1\n");
  printf("%d\n", counterccv_cli_output_level_and_above0);
  return (int)levels;
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

  // int-bounds
  case 0: {
    int level = 100;
    int benchRet = ccv_cli_output_level_and_above(level);
    break;
  }
  // big-arr
  case 1: {
    int level = 255;
    int benchRet = ccv_cli_output_level_and_above(level);
    break;
  }
  // big-arr-10x
  case 2: {
    int level = 10;
    int benchRet = ccv_cli_output_level_and_above(level);
    break;
  }
  case 3: {
    int level = 150;
    int benchRet = ccv_cli_output_level_and_above(level);
    break;
  }
  case 4: {
    int level = 200;
    int benchRet = ccv_cli_output_level_and_above(level);
    break;
  }
  default:
    usage();
    break;
  }

  return 0;
}
