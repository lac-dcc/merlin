// ========================================================================= //

// includes
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "limits.h"
#include "float.h"



#define JOTAI_NUM_RANDS_ 25

const unsigned rand_primes[JOTAI_NUM_RANDS_] = {179, 103, 479, 647, 229, 37, 271, 557, 263, 607, 18743, 50359, 21929, 48757, 98179, 12907, 52937, 64579, 49957, 52567, 507163, 149939, 412157, 680861, 757751};

int next_i() {
  int counter = 0;
  return rand_primes[(++counter)%JOTAI_NUM_RANDS_];
}

float next_f() {
  int counter = 0;
  return rand_primes[(++counter)%JOTAI_NUM_RANDS_] / 757751.0F;
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

#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct grub_sun_pc_block {int dummy; } ;
typedef  int /*<<< orphan*/  grub_uint16_t ;

/* Variables and functions */

__attribute__((used)) static int
grub_sun_is_valid (struct grub_sun_pc_block *label)
{
  grub_uint16_t *pos;
  grub_uint16_t sum = 0;

  for (pos = (grub_uint16_t *) label;
       pos < (grub_uint16_t *) (label + 1);
       pos++)
    sum ^= *pos;

  return ! sum;
}


// ------------------------------------------------------------------------- //




// ------------------------------------------------------------------------- //

int main(int argc, char *argv[]) {

    if (argc != 2) {
        usage();
        return 1;
    }

    int opt = atoi(argv[1]);
    switch(opt) {


    case 0:
    {
          int _len_label0 = 65025;
          struct grub_sun_pc_block * label = (struct grub_sun_pc_block *) malloc(_len_label0*sizeof(struct grub_sun_pc_block));
          for(int _i0 = 0; _i0 < _len_label0; _i0++) {
            label[_i0].dummy = ((-2 * (next_i()%2)) + 1) * next_i();
          }
          int benchRet = grub_sun_is_valid(label);
          
          free(label);
        
        break;
    }
    // big-arr-10x
    case 1:
    {
          int _len_label0 = 100;
          struct grub_sun_pc_block * label = (struct grub_sun_pc_block *) malloc(_len_label0*sizeof(struct grub_sun_pc_block));
          for(int _i0 = 0; _i0 < _len_label0; _i0++) {
            label[_i0].dummy = ((-2 * (next_i()%2)) + 1) * next_i();
          }
          int benchRet = grub_sun_is_valid(label);
          
          free(label);
        
        break;
    }
    case 2:
    {
          int _len_label0 = 10000;
          struct grub_sun_pc_block * label = (struct grub_sun_pc_block *) malloc(_len_label0*sizeof(struct grub_sun_pc_block));
          for(int _i0 = 0; _i0 < _len_label0; _i0++) {
            label[_i0].dummy = ((-2 * (next_i()%2)) + 1) * next_i();
          }
          int benchRet = grub_sun_is_valid(label);
          
          free(label);
        
        break;
    }
    case 3:
    {
          int _len_label0 = 22500;
          struct grub_sun_pc_block * label = (struct grub_sun_pc_block *) malloc(_len_label0*sizeof(struct grub_sun_pc_block));
          for(int _i0 = 0; _i0 < _len_label0; _i0++) {
            label[_i0].dummy = ((-2 * (next_i()%2)) + 1) * next_i();
          }
          int benchRet = grub_sun_is_valid(label);
          
          free(label);
        
        break;
    }
    case 4:
    {
          int _len_label0 = 40000;
          struct grub_sun_pc_block * label = (struct grub_sun_pc_block *) malloc(_len_label0*sizeof(struct grub_sun_pc_block));
          for(int _i0 = 0; _i0 < _len_label0; _i0++) {
            label[_i0].dummy = ((-2 * (next_i()%2)) + 1) * next_i();
          }
          int benchRet = grub_sun_is_valid(label);
          
          free(label);
        
        break;
    }

    default:
        usage();
        break;

    }

    return 0;
}
