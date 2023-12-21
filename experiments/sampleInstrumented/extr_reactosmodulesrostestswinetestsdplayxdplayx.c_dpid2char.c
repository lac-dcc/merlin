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
typedef size_t UINT;
typedef size_t DWORD;
typedef scalar_t__ DPID;

/* Variables and functions */
scalar_t__ DPID_SYSMSG;

__attribute__((used)) static char dpid2char(DPID *dpid, DWORD dpidSize,
                                            DPID idPlayer) {
  unsigned counterdpid2char0 = 0;

  DWORD tempdpidSize = dpidSize;

  UINT i;
  if (idPlayer == DPID_SYSMSG) {

    printf("Number of counters: 1\n");
    printf("At line 66 :");
    printf(" dpidSize\n");
    printf("Nesting depth: 1\n");
    printf("%ld %d\n", tempdpidSize, counterdpid2char0);
    return 'S';
  }
  for (i = 0; i < dpidSize; i++) {
    counterdpid2char0++;
    if (idPlayer == dpid[i]) {

      printf("Number of counters: 1\n");
      printf("At line 66 :");
      printf(" dpidSize\n");
      printf("Nesting depth: 1\n");
      printf("%ld %d\n", tempdpidSize, counterdpid2char0);
      return (char)(i + 48);
    }
  }

  printf("Number of counters: 1\n");
  printf("At line 66 :");
  printf(" dpidSize\n");
  printf("Nesting depth: 1\n");
  printf("%ld %d\n", tempdpidSize, counterdpid2char0);
  return '?';
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
    unsigned long dpidSize = 10;
    long idPlayer = 10;
    int _len_dpid0 = 100;
    long *dpid = (long *)malloc(_len_dpid0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_dpid0; _i0++) {
      dpid[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    char benchRet = dpid2char(dpid, dpidSize, idPlayer);
    free(dpid);

    break;
  }
  case 1: {
    unsigned long dpidSize = 100;
    long idPlayer = 100;
    int _len_dpid0 = 10000;
    long *dpid = (long *)malloc(_len_dpid0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_dpid0; _i0++) {
      dpid[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    char benchRet = dpid2char(dpid, dpidSize, idPlayer);
    free(dpid);

    break;
  }
  case 2: {
    unsigned long dpidSize = 255;
    long idPlayer = 255;
    int _len_dpid0 = 65025;
    long *dpid = (long *)malloc(_len_dpid0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_dpid0; _i0++) {
      dpid[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    char benchRet = dpid2char(dpid, dpidSize, idPlayer);
    free(dpid);

    break;
  }
  case 3: {
    unsigned long dpidSize = 150;
    long idPlayer = 150;
    int _len_dpid0 = 22500;
    long *dpid = (long *)malloc(_len_dpid0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_dpid0; _i0++) {
      dpid[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    char benchRet = dpid2char(dpid, dpidSize, idPlayer);
    free(dpid);

    break;
  }
  case 4: {
    unsigned long dpidSize = 200;
    long idPlayer = 200;
    int _len_dpid0 = 40000;
    long *dpid = (long *)malloc(_len_dpid0 * sizeof(long));
    for (int _i0 = 0; _i0 < _len_dpid0; _i0++) {
      dpid[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }
    char benchRet = dpid2char(dpid, dpidSize, idPlayer);
    free(dpid);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
