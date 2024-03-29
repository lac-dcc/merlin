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
struct op_system_config {
  int dummy;
};
struct op_register_config {
  unsigned long mux_select;
  unsigned long reset_values;
  unsigned long need_reset;
  scalar_t__ proc_mode;
};
struct op_counter_config {
  int event;
  unsigned long count;
  scalar_t__ enabled;
};

/* Variables and functions */

__attribute__((used)) static void ev67_reg_setup(struct op_register_config *reg,
                                                 struct op_counter_config *ctr,
                                                 struct op_system_config *sys) {
  unsigned counterev67_reg_setup0 = 0;

  unsigned long ctl, reset, need_reset, i;

  /* Select desired events.  */
  ctl = 1UL << 4; /* Enable ProfileMe mode. */

  /* The event numbers are chosen so we can use them directly if
     PCTR1 is enabled.  */
  if (ctr[1].enabled) {
    ctl |= (ctr[1].event & 3) << 2;
  } else {
    if (ctr[0].event == 0) { /* cycles */
      ctl |= 1UL << 2;
    }
  }
  reg->mux_select = ctl;

  /* Select logging options.  */
  /* ??? Need to come up with some mechanism to trace only
     selected processes.  EV67 does not have a mechanism to
     select kernel or user mode only.  For now, enable always.  */
  reg->proc_mode = 0;

  /* EV67 cannot change the width of the counters as with the
     other implementations.  But fortunately, we can write to
     the counters and set the value such that it will overflow
     at the right time.  */
  reset = need_reset = 0;
  for (i = 0; i < 2; ++i) {
    counterev67_reg_setup0++;
    unsigned long count = ctr[i].count;
    if (!ctr[i].enabled) {
      continue;
    }

    if (count > 0x100000) {
      count = 0x100000;
    }
    ctr[i].count = count;
    reset |= (0x100000 - count) << (i ? 6 : 28);
    if (count != 0x100000) {
      need_reset |= 1 << i;
    }
  }
  reg->reset_values = reset;
  reg->need_reset = need_reset;

  printf("Number of counters: 1\n");
  printf("At line 101 :");
  printf("\n");
  printf("Nesting depth: 0\n");
  printf("%d\n", counterev67_reg_setup0);
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
    // static_instructions_O0 : 71
    // dynamic_instructions_O0 : 111
    // -------------------------------
    // static_instructions_O1 : 50
    // dynamic_instructions_O1 : 76
    // -------------------------------
    // static_instructions_O2 : 41
    // dynamic_instructions_O2 : 41
    // -------------------------------
    // static_instructions_O3 : 41
    // dynamic_instructions_O3 : 41
    // -------------------------------
    // static_instructions_Ofast : 41
    // dynamic_instructions_Ofast : 41
    // -------------------------------
    // static_instructions_Os : 54
    // dynamic_instructions_Os : 80
    // -------------------------------
    // static_instructions_Oz : 58
    // dynamic_instructions_Oz : 86
    // -------------------------------

    int _len_reg0 = 65025;
    struct op_register_config *reg = (struct op_register_config *)malloc(
        _len_reg0 * sizeof(struct op_register_config));
    for (int _i0 = 0; _i0 < _len_reg0; _i0++) {
      reg[_i0].mux_select = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].reset_values = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].need_reset = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].proc_mode = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_ctr0 = 65025;
    struct op_counter_config *ctr = (struct op_counter_config *)malloc(
        _len_ctr0 * sizeof(struct op_counter_config));
    for (int _i0 = 0; _i0 < _len_ctr0; _i0++) {
      ctr[_i0].event = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].count = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].enabled = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_sys0 = 65025;
    struct op_system_config *sys = (struct op_system_config *)malloc(
        _len_sys0 * sizeof(struct op_system_config));
    for (int _i0 = 0; _i0 < _len_sys0; _i0++) {
      sys[_i0].dummy = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    ev67_reg_setup(reg, ctr, sys);
    free(reg);
    free(ctr);
    free(sys);

    break;
  }

  // big-arr-10x
  case 1: {
    int _len_reg0 = 100;
    struct op_register_config *reg = (struct op_register_config *)malloc(
        _len_reg0 * sizeof(struct op_register_config));
    for (int _i0 = 0; _i0 < _len_reg0; _i0++) {
      reg[_i0].mux_select = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].reset_values = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].need_reset = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].proc_mode = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_ctr0 = 100;
    struct op_counter_config *ctr = (struct op_counter_config *)malloc(
        _len_ctr0 * sizeof(struct op_counter_config));
    for (int _i0 = 0; _i0 < _len_ctr0; _i0++) {
      ctr[_i0].event = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].count = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].enabled = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_sys0 = 100;
    struct op_system_config *sys = (struct op_system_config *)malloc(
        _len_sys0 * sizeof(struct op_system_config));
    for (int _i0 = 0; _i0 < _len_sys0; _i0++) {
      sys[_i0].dummy = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    ev67_reg_setup(reg, ctr, sys);
    free(reg);
    free(ctr);
    free(sys);

    break;
  }
  case 2: {
    int _len_reg0 = 10000;
    struct op_register_config *reg = (struct op_register_config *)malloc(
        _len_reg0 * sizeof(struct op_register_config));
    for (int _i0 = 0; _i0 < _len_reg0; _i0++) {
      reg[_i0].mux_select = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].reset_values = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].need_reset = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].proc_mode = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_ctr0 = 10000;
    struct op_counter_config *ctr = (struct op_counter_config *)malloc(
        _len_ctr0 * sizeof(struct op_counter_config));
    for (int _i0 = 0; _i0 < _len_ctr0; _i0++) {
      ctr[_i0].event = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].count = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].enabled = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_sys0 = 10000;
    struct op_system_config *sys = (struct op_system_config *)malloc(
        _len_sys0 * sizeof(struct op_system_config));
    for (int _i0 = 0; _i0 < _len_sys0; _i0++) {
      sys[_i0].dummy = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    ev67_reg_setup(reg, ctr, sys);
    free(reg);
    free(ctr);
    free(sys);

    break;
  }
  case 3: {
    int _len_reg0 = 22500;
    struct op_register_config *reg = (struct op_register_config *)malloc(
        _len_reg0 * sizeof(struct op_register_config));
    for (int _i0 = 0; _i0 < _len_reg0; _i0++) {
      reg[_i0].mux_select = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].reset_values = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].need_reset = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].proc_mode = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_ctr0 = 22500;
    struct op_counter_config *ctr = (struct op_counter_config *)malloc(
        _len_ctr0 * sizeof(struct op_counter_config));
    for (int _i0 = 0; _i0 < _len_ctr0; _i0++) {
      ctr[_i0].event = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].count = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].enabled = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_sys0 = 22500;
    struct op_system_config *sys = (struct op_system_config *)malloc(
        _len_sys0 * sizeof(struct op_system_config));
    for (int _i0 = 0; _i0 < _len_sys0; _i0++) {
      sys[_i0].dummy = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    ev67_reg_setup(reg, ctr, sys);
    free(reg);
    free(ctr);
    free(sys);

    break;
  }
  case 4: {
    int _len_reg0 = 40000;
    struct op_register_config *reg = (struct op_register_config *)malloc(
        _len_reg0 * sizeof(struct op_register_config));
    for (int _i0 = 0; _i0 < _len_reg0; _i0++) {
      reg[_i0].mux_select = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].reset_values = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].need_reset = ((-2 * (next_i() % 2)) + 1) * next_i();
      reg[_i0].proc_mode = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_ctr0 = 40000;
    struct op_counter_config *ctr = (struct op_counter_config *)malloc(
        _len_ctr0 * sizeof(struct op_counter_config));
    for (int _i0 = 0; _i0 < _len_ctr0; _i0++) {
      ctr[_i0].event = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].count = ((-2 * (next_i() % 2)) + 1) * next_i();
      ctr[_i0].enabled = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    int _len_sys0 = 40000;
    struct op_system_config *sys = (struct op_system_config *)malloc(
        _len_sys0 * sizeof(struct op_system_config));
    for (int _i0 = 0; _i0 < _len_sys0; _i0++) {
      sys[_i0].dummy = ((-2 * (next_i() % 2)) + 1) * next_i();
    }

    ev67_reg_setup(reg, ctr, sys);
    free(reg);
    free(ctr);
    free(sys);

    break;
  }

  default:
    usage();
    break;
  }

  return 0;
}
