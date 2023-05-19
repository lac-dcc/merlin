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
       0            big-arr\n\
       1            big-arr-10x\n\
       2            empty\n\
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
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int used; int count; } ;
typedef  TYPE_1__ hnode ;

/* Variables and functions */

__attribute__((used)) static int huff_smallest_node(hnode *hnodes, int num_hnodes) {
    int i;
    int best, best_node;

    best = 99999999;
    best_node = -1;
    for(i = 0; i < num_hnodes; i++) {
        if(hnodes[i].used)
            continue;
        if(!hnodes[i].count)
            continue;
        if(hnodes[i].count < best) {
            best = hnodes[i].count;
            best_node = i;
        }
    }

    if(best_node == -1)
        return -1;
    hnodes[best_node].used = 1;
    return best_node;
}

// ------------------------------------------------------------------------- //

int main(int argc, char *argv[]) {

    if (argc != 2) {
        usage();
        return 1;
    }

    int opt = atoi(argv[1]);
    switch(opt) {

    // big-arr
    case 0:
    {
          int num_hnodes = 255;
        
          int _len_hnodes0 = 65025;
          struct TYPE_3__ * hnodes = (struct TYPE_3__ *) malloc(_len_hnodes0*sizeof(struct TYPE_3__));
          for(int _i0 = 0; _i0 < _len_hnodes0; _i0++) {
              hnodes[_i0].used = ((-2 * (next_i()%2)) + 1) * next_i();
          hnodes[_i0].count = ((-2 * (next_i()%2)) + 1) * next_i();
        
          }
        
          int benchRet = huff_smallest_node(hnodes,num_hnodes);
          printf("%d\n", benchRet); 
          free(hnodes);
        
        break;
    }
    // big-arr-10x
    case 1:
    {
          int num_hnodes = 10;
        
          int _len_hnodes0 = 100;
          struct TYPE_3__ * hnodes = (struct TYPE_3__ *) malloc(_len_hnodes0*sizeof(struct TYPE_3__));
          for(int _i0 = 0; _i0 < _len_hnodes0; _i0++) {
              hnodes[_i0].used = ((-2 * (next_i()%2)) + 1) * next_i();
          hnodes[_i0].count = ((-2 * (next_i()%2)) + 1) * next_i();
        
          }
        
          int benchRet = huff_smallest_node(hnodes,num_hnodes);
          printf("%d\n", benchRet); 
          free(hnodes);
        
        break;
    }
    // empty
    case 2:
    {
          int num_hnodes = ((-2 * (next_i()%2)) + 1) * next_i();
        
          int _len_hnodes0 = 1;
          struct TYPE_3__ * hnodes = (struct TYPE_3__ *) malloc(_len_hnodes0*sizeof(struct TYPE_3__));
          for(int _i0 = 0; _i0 < _len_hnodes0; _i0++) {
              hnodes[_i0].used = ((-2 * (next_i()%2)) + 1) * next_i();
          hnodes[_i0].count = ((-2 * (next_i()%2)) + 1) * next_i();
        
          }
        
          int benchRet = huff_smallest_node(hnodes,num_hnodes);
          printf("%d\n", benchRet); 
          free(hnodes);
        
        break;
    }
    default:
        usage();
        break;

    }

    return 0;
}