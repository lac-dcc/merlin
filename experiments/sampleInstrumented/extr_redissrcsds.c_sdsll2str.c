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

int sdsll2str(char *s, long long value) {
  unsigned countersdsll2str1 = 0;
  unsigned countersdsll2str0 = 0;

  char *temps = s;
  long long tempvalue = value;

  char *p, aux;
  unsigned long long v;
  size_t l;

  /* Generate the string representation, this method produces
   * an reversed string. */
  v = (value < 0) ? -value : value;
  p = s;
  do {
    countersdsll2str0++;
    *p++ = '0' + (v % 10);
    v /= 10;
  } while (v);
  if (value < 0) {
    *p++ = '-';
  }

  /* Compute length and add null term. */
  l = p - s;
  *p = '\0';

  /* Reverse the string. */
  p--;
  while (s < p) {
    countersdsll2str1++;
    aux = *s;
    *s = *p;
    *p = aux;
    s++;
    p--;
  }

  printf("Maximum nesting depth: 1\n");
  printf("Number of loops: 2\n");
  printf("at line 79 :");
  printf(" s\n");
  printf("at line 65 :");
  printf(" value\n");
  printf("%c %d\n", *temps, countersdsll2str1);
  printf(" %d\n", tempvalue, countersdsll2str0);
  return l;
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
    long long value = 10;
    int _len_s0 = 100;
    char *s = (char *)malloc(_len_s0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = sdsll2str(s, value);

    free(s);

    break;
  }
  case 1: {
    long long value = 100;
    int _len_s0 = 10000;
    char *s = (char *)malloc(_len_s0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = sdsll2str(s, value);

    free(s);

    break;
  }
  case 2: {
    long long value = 255;
    int _len_s0 = 65025;
    char *s = (char *)malloc(_len_s0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = sdsll2str(s, value);

    free(s);

    break;
  }
  case 3: {
    long long value = 150;
    int _len_s0 = 22500;
    char *s = (char *)malloc(_len_s0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = sdsll2str(s, value);

    free(s);

    break;
  }
  case 4: {
    long long value = 200;
    int _len_s0 = 40000;
    char *s = (char *)malloc(_len_s0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = sdsll2str(s, value);

    free(s);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
