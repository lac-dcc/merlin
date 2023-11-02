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
       3            empty\n\
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
typedef int /*<<< orphan*/ v;

/* Variables and functions */

__attribute__((used)) static unsigned long rev(unsigned long v) {
  unsigned counterrev0 = 0;

  unsigned long tempv = v;

  unsigned long s = 8 * sizeof(v); // bit size; must be power of 2
  unsigned long mask = ~0;
  while ((s >>= 1) > 0) {
    counterrev0++;
    mask ^= (mask << s);
    v = ((v >> s) & mask) | ((v << s) & ~mask);
  }

  printf("Maximum nesting depth: 1\n");
  printf("Number of loops: 1\n");
  printf("at line 63 :");
  printf(" v\n");
  printf("%ld %d\n", tempv, counterrev0);
  return v;
}

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
    // static_instructions_O0 : 32
    // dynamic_instructions_O0 : 157
    // -------------------------------
    // static_instructions_O1 : 22
    // dynamic_instructions_O1 : 87
    // -------------------------------
    // static_instructions_O2 : 25
    // dynamic_instructions_O2 : 25
    // -------------------------------
    // static_instructions_O3 : 25
    // dynamic_instructions_O3 : 25
    // -------------------------------
    // static_instructions_Ofast : 25
    // dynamic_instructions_Ofast : 25
    // -------------------------------
    // static_instructions_Os : 20
    // dynamic_instructions_Os : 85
    // -------------------------------
    // static_instructions_Oz : 22
    // dynamic_instructions_Oz : 99
    // -------------------------------

    unsigned long v = 100;

    unsigned long benchRet = rev(v);

    break;
  }

  // big-arr
  case 1: {
    // static_instructions_O0 : 32
    // dynamic_instructions_O0 : 157
    // -------------------------------
    // static_instructions_O1 : 22
    // dynamic_instructions_O1 : 87
    // -------------------------------
    // static_instructions_O2 : 25
    // dynamic_instructions_O2 : 25
    // -------------------------------
    // static_instructions_O3 : 25
    // dynamic_instructions_O3 : 25
    // -------------------------------
    // static_instructions_Ofast : 25
    // dynamic_instructions_Ofast : 25
    // -------------------------------
    // static_instructions_Os : 20
    // dynamic_instructions_Os : 85
    // -------------------------------
    // static_instructions_Oz : 22
    // dynamic_instructions_Oz : 99
    // -------------------------------

    unsigned long v = 255;

    unsigned long benchRet = rev(v);

    break;
  }

  // big-arr-10x
  case 2: {
    // static_instructions_O0 : 32
    // dynamic_instructions_O0 : 157
    // -------------------------------
    // static_instructions_O1 : 22
    // dynamic_instructions_O1 : 87
    // -------------------------------
    // static_instructions_O2 : 25
    // dynamic_instructions_O2 : 25
    // -------------------------------
    // static_instructions_O3 : 25
    // dynamic_instructions_O3 : 25
    // -------------------------------
    // static_instructions_Ofast : 25
    // dynamic_instructions_Ofast : 25
    // -------------------------------
    // static_instructions_Os : 20
    // dynamic_instructions_Os : 85
    // -------------------------------
    // static_instructions_Oz : 22
    // dynamic_instructions_Oz : 99
    // -------------------------------

    unsigned long v = 10;

    unsigned long benchRet = rev(v);

    break;
  }
  case 3: {
    // static_instructions_O0 : 32
    // dynamic_instructions_O0 : 157
    // -------------------------------
    // static_instructions_O1 : 22
    // dynamic_instructions_O1 : 87
    // -------------------------------
    // static_instructions_O2 : 25
    // dynamic_instructions_O2 : 25
    // -------------------------------
    // static_instructions_O3 : 25
    // dynamic_instructions_O3 : 25
    // -------------------------------
    // static_instructions_Ofast : 25
    // dynamic_instructions_Ofast : 25
    // -------------------------------
    // static_instructions_Os : 20
    // dynamic_instructions_Os : 85
    // -------------------------------
    // static_instructions_Oz : 22
    // dynamic_instructions_Oz : 99
    // -------------------------------

    unsigned long v = 150;

    unsigned long benchRet = rev(v);

    break;
  }
  case 4: {
    // static_instructions_O0 : 32
    // dynamic_instructions_O0 : 157
    // -------------------------------
    // static_instructions_O1 : 22
    // dynamic_instructions_O1 : 87
    // -------------------------------
    // static_instructions_O2 : 25
    // dynamic_instructions_O2 : 25
    // -------------------------------
    // static_instructions_O3 : 25
    // dynamic_instructions_O3 : 25
    // -------------------------------
    // static_instructions_Ofast : 25
    // dynamic_instructions_Ofast : 25
    // -------------------------------
    // static_instructions_Os : 20
    // dynamic_instructions_Os : 85
    // -------------------------------
    // static_instructions_Oz : 22
    // dynamic_instructions_Oz : 99
    // -------------------------------

    unsigned long v = 200;

    unsigned long benchRet = rev(v);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
