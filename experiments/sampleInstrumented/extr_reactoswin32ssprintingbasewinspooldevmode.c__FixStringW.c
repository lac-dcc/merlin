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
typedef int /*<<< orphan*/ WCHAR;
typedef scalar_t__ *PWSTR;
typedef int DWORD;

/* Variables and functions */

__attribute__((used)) static __inline void _FixStringW(PWSTR String,
                                                       DWORD cbString) {
  unsigned counter_FixStringW0 = 0;

  PWSTR tempString = String;

  const PWSTR pLastCharacter = &String[cbString / sizeof(WCHAR) - 1];
  PWSTR p = String;

  while (*p) {
    counter_FixStringW0++;
    if (p == pLastCharacter) {
      *p = 0;
      break;
    }

    p++;
  }

  printf("Number of counters: 1\n");
  printf("At line 64 :");
  printf(" String\n");
  printf("Nesting depth: 1\n");
  printf("%ld %d\n", *tempString, counter_FixStringW0);
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
    int cbString = 10;
    int _len_String0 = 100;
    long *String = (long *)malloc(_len_String0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_String0; _i0++) {
      String[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    _FixStringW(String, cbString);
    free(String);

    break;
  }
  case 1: {
    int cbString = 100;
    int _len_String0 = 10000;
    long *String = (long *)malloc(_len_String0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_String0; _i0++) {
      String[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    _FixStringW(String, cbString);
    free(String);

    break;
  }
  case 2: {
    int cbString = 255;
    int _len_String0 = 65025;
    long *String = (long *)malloc(_len_String0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_String0; _i0++) {
      String[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    _FixStringW(String, cbString);
    free(String);

    break;
  }
  case 3: {
    int cbString = 150;
    int _len_String0 = 22500;
    long *String = (long *)malloc(_len_String0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_String0; _i0++) {
      String[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    _FixStringW(String, cbString);
    free(String);

    break;
  }
  case 4: {
    int cbString = 200;
    int _len_String0 = 40000;
    long *String = (long *)malloc(_len_String0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_String0; _i0++) {
      String[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    _FixStringW(String, cbString);
    free(String);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
