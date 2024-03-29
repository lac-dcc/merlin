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
struct cris_disasm_data {
  scalar_t__ distype;
};

/* Variables and functions */
scalar_t__ cris_dis_v32;

__attribute__((used)) static char *print_flags(struct cris_disasm_data *disdata,
                                               unsigned int insn, char *cp) {
  unsigned counterprint_flags0 = 0;

  /* Use the v8 (Etrax 100) flag definitions for disassembly.
     The differences with v0 (Etrax 1..4) vs. Svinto are:
      v0 'd' <=> v8 'm'
      v0 'e' <=> v8 'b'.
     FIXME: Emit v0..v3 flag names somehow.  */
  static const char v8_fnames[] = "cvznxibm";
  static const char v32_fnames[] = "cvznxiup";
  const char *fnames =
      disdata->distype == cris_dis_v32 ? v32_fnames : v8_fnames;

  unsigned char flagbits = (((insn >> 8) & 0xf0) | (insn & 15));
  int i;

  for (i = 0; i < 8; i++) {
    counterprint_flags0++;
    if (flagbits & (1 << i)) {
      *cp++ = fnames[i];
    }
  }

  printf("Number of counters: 1\n");
  printf("At line 76 :");
  printf("\n");
  printf("Nesting depth: 0\n");
  printf("%d\n", counterprint_flags0);
  return cp;
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
    unsigned int insn = 255;

    int _len_disdata0 = 65025;
    struct cris_disasm_data *disdata = (struct cris_disasm_data *)malloc(
        _len_disdata0 * sizeof(struct cris_disasm_data));
    for (int _i0 = 0; _i0 < _len_disdata0; _i0++) {
      disdata[_i0].distype = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_cp0 = 65025;
    char *cp = (char *)malloc(_len_cp0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_cp0; _i0++) {
      cp[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    char *benchRet = print_flags(disdata, insn, cp);

    free(disdata);
    free(cp);

    break;
  }
  // big-arr-10x
  case 1: {
    unsigned int insn = 10;

    int _len_disdata0 = 100;
    struct cris_disasm_data *disdata = (struct cris_disasm_data *)malloc(
        _len_disdata0 * sizeof(struct cris_disasm_data));
    for (int _i0 = 0; _i0 < _len_disdata0; _i0++) {
      disdata[_i0].distype = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_cp0 = 100;
    char *cp = (char *)malloc(_len_cp0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_cp0; _i0++) {
      cp[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    char *benchRet = print_flags(disdata, insn, cp);

    free(disdata);
    free(cp);

    break;
  }
  case 2: {
    unsigned int insn = 100;

    int _len_disdata0 = 10000;
    struct cris_disasm_data *disdata = (struct cris_disasm_data *)malloc(
        _len_disdata0 * sizeof(struct cris_disasm_data));
    for (int _i0 = 0; _i0 < _len_disdata0; _i0++) {
      disdata[_i0].distype = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_cp0 = 10000;
    char *cp = (char *)malloc(_len_cp0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_cp0; _i0++) {
      cp[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    char *benchRet = print_flags(disdata, insn, cp);

    free(disdata);
    free(cp);

    break;
  }
  case 3: {
    unsigned int insn = 150;

    int _len_disdata0 = 22500;
    struct cris_disasm_data *disdata = (struct cris_disasm_data *)malloc(
        _len_disdata0 * sizeof(struct cris_disasm_data));
    for (int _i0 = 0; _i0 < _len_disdata0; _i0++) {
      disdata[_i0].distype = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_cp0 = 22500;
    char *cp = (char *)malloc(_len_cp0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_cp0; _i0++) {
      cp[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    char *benchRet = print_flags(disdata, insn, cp);

    free(disdata);
    free(cp);

    break;
  }
  case 4: {
    unsigned int insn = 200;

    int _len_disdata0 = 40000;
    struct cris_disasm_data *disdata = (struct cris_disasm_data *)malloc(
        _len_disdata0 * sizeof(struct cris_disasm_data));
    for (int _i0 = 0; _i0 < _len_disdata0; _i0++) {
      disdata[_i0].distype = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_cp0 = 40000;
    char *cp = (char *)malloc(_len_cp0 * sizeof(char));
    for (int _i0 = 0; _i0 < _len_cp0; _i0++) {
      cp[_i0] = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    char *benchRet = print_flags(disdata, insn, cp);

    free(disdata);
    free(cp);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
