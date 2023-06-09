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

__attribute__((used)) static int addr_crc(unsigned char *addr) {
  unsigned counteraddr_crc = 0;

  int crc = 0;
  int i;

  for (i = 0; i < 6; i++) {
    counteraddr_crc++;
    int j;

    crc = (crc ^ addr[i]) << 8;
    for (j = 7; j >= 0; j--) {
      counteraddr_crc++;
      if (crc & (0x100 << j)) {
        crc ^= 0x107 << j;
      }
    }
  }

  printf("%d\n", counteraddr_crc);
  return crc;
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
    int _len_addr0 = 65025;
    unsigned char *addr =
        (unsigned char *)malloc(_len_addr0 * sizeof(unsigned char));
    for (int _i0 = 0; _i0 < _len_addr0; _i0++) {
      addr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int benchRet = addr_crc(addr);
    // printf("%d\n", benchRet);
    free(addr);

    break;
  }
  // big-arr-10x
  case 1: {
    int _len_addr0 = 100;
    unsigned char *addr =
        (unsigned char *)malloc(_len_addr0 * sizeof(unsigned char));
    for (int _i0 = 0; _i0 < _len_addr0; _i0++) {
      addr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int benchRet = addr_crc(addr);
    // printf("%d\n", benchRet);
    free(addr);

    break;
  }
  default:
    usage();
    break;
  }

  return 0;
}
