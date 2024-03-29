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

void scsi_sanitize_inquiry_string(unsigned char *s, int len) {
  unsigned counterscsi_sanitize_inquiry_string0 = 0;

  int templen = len;

  int terminated = 0;

  for (; len > 0; (--len, ++s)) {
    counterscsi_sanitize_inquiry_string0++;
    if (*s == 0) {
      terminated = 1;
    }
    if (terminated || *s < 0x20 || *s > 0x7e) {
      *s = ' ';
    }
  }

  printf("Number of counters: 1\n");
  printf("At line 59 :");
  printf(" len\n");
  printf("Nesting depth: 1\n");
  printf("%d %d\n", templen, counterscsi_sanitize_inquiry_string0);
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
    int len = 10;
    int _len_s0 = 100;
    unsigned char *s = (unsigned char *)malloc(_len_s0 * sizeof(unsigned char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    scsi_sanitize_inquiry_string(s, len);
    free(s);

    break;
  }
  case 1: {
    int len = 100;
    int _len_s0 = 10000;
    unsigned char *s = (unsigned char *)malloc(_len_s0 * sizeof(unsigned char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    scsi_sanitize_inquiry_string(s, len);
    free(s);

    break;
  }
  case 2: {
    int len = 255;
    int _len_s0 = 65025;
    unsigned char *s = (unsigned char *)malloc(_len_s0 * sizeof(unsigned char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    scsi_sanitize_inquiry_string(s, len);
    free(s);

    break;
  }
  case 3: {
    int len = 150;
    int _len_s0 = 22500;
    unsigned char *s = (unsigned char *)malloc(_len_s0 * sizeof(unsigned char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    scsi_sanitize_inquiry_string(s, len);
    free(s);

    break;
  }
  case 4: {
    int len = 200;
    int _len_s0 = 40000;
    unsigned char *s = (unsigned char *)malloc(_len_s0 * sizeof(unsigned char));
    for (int _i0 = 0; _i0 < _len_s0; _i0++) {
      s[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    scsi_sanitize_inquiry_string(s, len);
    free(s);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
