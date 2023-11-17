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
typedef int uint8_t;
typedef int uint16_t;

/* Variables and functions */

__attribute__((used)) static uint16_t crc16(uint8_t *ptr, unsigned int len) {
  unsigned countercrc161 = 0;
  unsigned countercrc160 = 0;

  unsigned int templen = len;

  uint16_t crc = 0xFFFF;
  uint8_t i;

  while (len--) {
    countercrc160++;
    crc ^= *ptr++;
    for (i = 0; i < 8; i++) {
      countercrc161++;
      if (crc & 0x01) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }

  printf("Number of counters: 2\n");
  printf("At line 64 :");
  printf(" len\n");
  printf("Nesting depth: 1\n");
  printf("At line 62 :");
  printf(" len\n");
  printf("Nesting depth: 1\n");
  printf("%u %d\n", templen, countercrc161);
  printf("%u %d\n", templen, countercrc160);
  return crc;
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
    unsigned int len = 10;
    int _len_ptr0 = 100;
    int *ptr = (int *)malloc(_len_ptr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_ptr0; _i0++) {
      ptr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = crc16(ptr, len);
    free(ptr);

    break;
  }
  case 1: {
    unsigned int len = 100;
    int _len_ptr0 = 10000;
    int *ptr = (int *)malloc(_len_ptr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_ptr0; _i0++) {
      ptr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = crc16(ptr, len);
    free(ptr);

    break;
  }
  case 2: {
    unsigned int len = 255;
    int _len_ptr0 = 65025;
    int *ptr = (int *)malloc(_len_ptr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_ptr0; _i0++) {
      ptr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = crc16(ptr, len);
    free(ptr);

    break;
  }
  case 3: {
    unsigned int len = 150;
    int _len_ptr0 = 22500;
    int *ptr = (int *)malloc(_len_ptr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_ptr0; _i0++) {
      ptr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = crc16(ptr, len);
    free(ptr);

    break;
  }
  case 4: {
    unsigned int len = 200;
    int _len_ptr0 = 40000;
    int *ptr = (int *)malloc(_len_ptr0 * sizeof(int));
    for (int _i0 = 0; _i0 < _len_ptr0; _i0++) {
      ptr[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = crc16(ptr, len);
    free(ptr);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
