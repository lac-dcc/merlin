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
typedef int stb_uint;
typedef scalar_t__ stb_uchar;

/* Variables and functions */

stb_uint stb_adler32(stb_uint adler32, stb_uchar *buffer, stb_uint buflen) {
  unsigned counterstb_adler320 = 0;
  unsigned counterstb_adler322 = 0;
  unsigned counterstb_adler321 = 0;

  stb_uint tempbuflen = buflen;

  const unsigned long ADLER_MOD = 65521;
  unsigned long s1 = adler32 & 0xffff, s2 = adler32 >> 16;
  unsigned long blocklen, i;

  blocklen = buflen % 5552;
  while (buflen) {
    counterstb_adler320++;
    for (i = 0; i + 7 < blocklen; i += 8) {
      counterstb_adler321++;
      s1 += buffer[0], s2 += s1;
      s1 += buffer[1], s2 += s1;
      s1 += buffer[2], s2 += s1;
      s1 += buffer[3], s2 += s1;
      s1 += buffer[4], s2 += s1;
      s1 += buffer[5], s2 += s1;
      s1 += buffer[6], s2 += s1;
      s1 += buffer[7], s2 += s1;

      buffer += 8;
    }

    for (; i < blocklen; ++i) {
      counterstb_adler322++;
      s1 += *buffer++, s2 += s1;
    }

    s1 %= ADLER_MOD, s2 %= ADLER_MOD;
    buflen -= blocklen;
    blocklen = 5552;
  }

  printf("Maximum nesting depth: 2\n");
  printf("Number of loops: 3\n");
  printf("at line 64 :");
  printf(" buflen\n");
  printf("at line 78 :");
  printf(" buflen\n");
  printf("at line 65 :");
  printf(" buflen\n");
  printf("%d %d\n", tempbuflen, counterstb_adler320);
  printf("%d %d\n", tempbuflen, counterstb_adler322);
  printf("%d %d\n", tempbuflen, counterstb_adler321);
  return (s2 << 16) + s1;
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
    int adler32 = 10;
    int buflen = 10;
    int _len_buffer0 = 100;
    long *buffer = (long *)malloc(_len_buffer0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_buffer0; _i0++) {
      buffer[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = stb_adler32(adler32, buffer, buflen);
    free(buffer);

    break;
  }
  case 1: {
    int adler32 = 100;
    int buflen = 100;
    int _len_buffer0 = 10000;
    long *buffer = (long *)malloc(_len_buffer0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_buffer0; _i0++) {
      buffer[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = stb_adler32(adler32, buffer, buflen);
    free(buffer);

    break;
  }
  case 2: {
    int adler32 = 255;
    int buflen = 255;
    int _len_buffer0 = 65025;
    long *buffer = (long *)malloc(_len_buffer0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_buffer0; _i0++) {
      buffer[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = stb_adler32(adler32, buffer, buflen);
    free(buffer);

    break;
  }
  case 3: {
    int adler32 = 150;
    int buflen = 150;
    int _len_buffer0 = 22500;
    long *buffer = (long *)malloc(_len_buffer0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_buffer0; _i0++) {
      buffer[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = stb_adler32(adler32, buffer, buflen);
    free(buffer);

    break;
  }
  case 4: {
    int adler32 = 200;
    int buflen = 200;
    int _len_buffer0 = 40000;
    long *buffer = (long *)malloc(_len_buffer0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_buffer0; _i0++) {
      buffer[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = stb_adler32(adler32, buffer, buflen);
    free(buffer);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
