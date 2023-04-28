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
       0            big-arr-10x\n\
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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ memid; } ;
struct TYPE_6__ {TYPE_1__ funcdesc; } ;
typedef  TYPE_2__ TLBFuncDesc ;
typedef  scalar_t__ MEMBERID ;

/* Variables and functions */

__attribute__((used)) static inline TLBFuncDesc *TLB_get_funcdesc_by_memberid(TLBFuncDesc *funcdescs,
        UINT n, MEMBERID memid)
{
    while(n){
        if(funcdescs->funcdesc.memid == memid)
            return funcdescs;
        ++funcdescs;
        --n;
    }
    return NULL;
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

    // big-arr-10x
    case 0:
    {
          long n = 10;
          long memid = 10;
          int _len_funcdescs0 = 100;
          struct TYPE_6__ * funcdescs = (struct TYPE_6__ *) malloc(_len_funcdescs0*sizeof(struct TYPE_6__));
          for(int _i0 = 0; _i0 < _len_funcdescs0; _i0++) {
            funcdescs[_i0].funcdesc.memid = ((-2 * (next_i()%2)) + 1) * next_i();
          }
          struct TYPE_6__ * benchRet = TLB_get_funcdesc_by_memberid(funcdescs,n,memid);
          free(funcdescs);
        
        break;
    }

    default:
        usage();
        break;

    }

    return 0;
}
