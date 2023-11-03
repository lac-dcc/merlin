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
typedef int uint32_t;
typedef int uint16_t;
struct seeprom_config {
  int checksum;
};

/* Variables and functions */

int ahc_verify_cksum(struct seeprom_config *sc) {
  unsigned counterahc_verify_cksum0 = 0;

  struct seeprom_config *tempsc = sc;

  int i;
  int maxaddr;
  uint32_t checksum;
  uint16_t *scarray;

  maxaddr = (sizeof(*sc) / 2) - 1;
  checksum = 0;
  scarray = (uint16_t *)sc;

  for (i = 0; i < maxaddr; i++) {
    counterahc_verify_cksum0++;
    checksum = checksum + scarray[i];
  }
  if (checksum == 0 || (checksum & 0xFFFF) != sc->checksum) {

    printf("Maximum nesting depth: 1\n");
    printf("Number of loops: 1\n");
    printf("at line 72 :");
    printf(" sc\n");
    printf(" %d\n", *tempsc, counterahc_verify_cksum0);
    return (0);
  } else {

    printf("Maximum nesting depth: 1\n");
    printf("Number of loops: 1\n");
    printf("at line 72 :");
    printf(" sc\n");
    printf(" %d\n", *tempsc, counterahc_verify_cksum0);
    return (1);
  }
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
    int _len_sc0 = 65025;
    struct seeprom_config *sc = (struct seeprom_config *)malloc(
        _len_sc0 * sizeof(struct seeprom_config));
    for (int _i0 = 0; _i0 < _len_sc0; _i0++) {
      sc[_i0].checksum = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = ahc_verify_cksum(sc);

    free(sc);

    break;
  }
  // big-arr-10x
  case 1: {
    int _len_sc0 = 100;
    struct seeprom_config *sc = (struct seeprom_config *)malloc(
        _len_sc0 * sizeof(struct seeprom_config));
    for (int _i0 = 0; _i0 < _len_sc0; _i0++) {
      sc[_i0].checksum = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = ahc_verify_cksum(sc);

    free(sc);

    break;
  }
  case 2: {
    int _len_sc0 = 10000;
    struct seeprom_config *sc = (struct seeprom_config *)malloc(
        _len_sc0 * sizeof(struct seeprom_config));
    for (int _i0 = 0; _i0 < _len_sc0; _i0++) {
      sc[_i0].checksum = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = ahc_verify_cksum(sc);

    free(sc);

    break;
  }
  case 3: {
    int _len_sc0 = 25000;
    struct seeprom_config *sc = (struct seeprom_config *)malloc(
        _len_sc0 * sizeof(struct seeprom_config));
    for (int _i0 = 0; _i0 < _len_sc0; _i0++) {
      sc[_i0].checksum = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = ahc_verify_cksum(sc);

    free(sc);

    break;
  }
  case 4: {
    int _len_sc0 = 40000;
    struct seeprom_config *sc = (struct seeprom_config *)malloc(
        _len_sc0 * sizeof(struct seeprom_config));
    for (int _i0 = 0; _i0 < _len_sc0; _i0++) {
      sc[_i0].checksum = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    int benchRet = ahc_verify_cksum(sc);

    free(sc);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}