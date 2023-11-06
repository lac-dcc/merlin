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

__attribute__((used)) static void ui2a(unsigned int num, unsigned int base,
                                       int uc, char *bf) {
  unsigned counterui2a0 = 0;
  unsigned counterui2a1 = 0;

  unsigned int tempnum = num;
  unsigned int tempbase = base;

  int n = 0;
  unsigned int d = 1;
  while (num / d >= base) {
    counterui2a0++;
    d *= base;
  }
  while (d != 0) {
    counterui2a1++;
    int dgt = num / d;
    num %= d;
    d /= base;
    if (n || dgt > 0 || d == 0) {
      *bf++ = dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
      ++n;
    }
  }
  *bf = 0;

  printf("Number of counters: 2\n");
  printf("At line 60 :");
  printf(" num base\n");
  printf("Nesting depth: 1\n");
  printf("At line 63 :");
  printf(" base\n");
  printf("Nesting depth: 1\n");
  printf("%u %u %d\n", tempnum, tempbase, counterui2a0);
  printf("%u %d\n", tempbase, counterui2a1);
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
    unsigned int num = 10;
    unsigned int base = 10;
    int uc = 10;
    int _len_bf0 = 100;
    char *bf = (char *)malloc(_len_bf0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_bf0; _i0++) {
      bf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    ui2a(num, base, uc, bf);
    free(bf);

    break;
  }
  case 1: {
    unsigned int num = 100;
    unsigned int base = 100;
    int uc = 100;
    int _len_bf0 = 10000;
    char *bf = (char *)malloc(_len_bf0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_bf0; _i0++) {
      bf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    ui2a(num, base, uc, bf);
    free(bf);

    break;
  }
  case 2: {
    unsigned int num = 255;
    unsigned int base = 255;
    int uc = 255;
    int _len_bf0 = 65025;
    char *bf = (char *)malloc(_len_bf0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_bf0; _i0++) {
      bf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    ui2a(num, base, uc, bf);
    free(bf);

    break;
  }
  case 3: {
    unsigned int num = 150;
    unsigned int base = 150;
    int uc = 150;
    int _len_bf0 = 22500;
    char *bf = (char *)malloc(_len_bf0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_bf0; _i0++) {
      bf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    ui2a(num, base, uc, bf);
    free(bf);

    break;
  }
  case 4: {
    unsigned int num = 200;
    unsigned int base = 200;
    int uc = 200;
    int _len_bf0 = 40000;
    char *bf = (char *)malloc(_len_bf0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_bf0; _i0++) {
      bf[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    ui2a(num, base, uc, bf);
    free(bf);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
