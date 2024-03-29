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

/* Variables and functions */

__attribute__((used)) static inline void mix_audio(float *p_out, float *p_in,
		size_t pos, size_t count)
{
	register float *out = p_out;
	register float *in = p_in + pos;
	register float *end = in + count;

	while (in < end)
		*(out++) += *(in++);
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
          // static_instructions_O0 : 35
          // dynamic_instructions_O0 : 3848
          // ------------------------------- 
          // static_instructions_O1 : 17
          // dynamic_instructions_O1 : 1795
          // ------------------------------- 
          // static_instructions_O2 : 96
          // dynamic_instructions_O2 : 404
          // ------------------------------- 
          // static_instructions_O3 : 96
          // dynamic_instructions_O3 : 404
          // ------------------------------- 
          // static_instructions_Ofast : 96
          // dynamic_instructions_Ofast : 404
          // ------------------------------- 
          // static_instructions_Os : 15
          // dynamic_instructions_Os : 1793
          // ------------------------------- 
          // static_instructions_Oz : 14
          // dynamic_instructions_Oz : 2048
          // ------------------------------- 

          unsigned long pos = 255;
        
          unsigned long count = 255;
        
          int _len_p_out0 = 65025;
          float * p_out = (float *) malloc(_len_p_out0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_out0; _i0++) {
            p_out[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          int _len_p_in0 = 65025;
          float * p_in = (float *) malloc(_len_p_in0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_in0; _i0++) {
            p_in[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          mix_audio(p_out,p_in,pos,count);
          free(p_out);
          free(p_in);
        
        break;
    }


    // big-arr-10x
    case 1:
    {
          unsigned long pos = 10;
        
          unsigned long count = 10;
        
          int _len_p_out0 = 100;
          float * p_out = (float *) malloc(_len_p_out0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_out0; _i0++) {
            p_out[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          int _len_p_in0 = 100;
          float * p_in = (float *) malloc(_len_p_in0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_in0; _i0++) {
            p_in[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          mix_audio(p_out,p_in,pos,count);
          free(p_out);
          free(p_in);
        
        break;
    }
    case 2:
    {
          unsigned long pos = 100;
        
          unsigned long count = 100;
        
          int _len_p_out0 = 10000;
          float * p_out = (float *) malloc(_len_p_out0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_out0; _i0++) {
            p_out[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          int _len_p_in0 = 10000;
          float * p_in = (float *) malloc(_len_p_in0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_in0; _i0++) {
            p_in[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          mix_audio(p_out,p_in,pos,count);
          free(p_out);
          free(p_in);
        
        break;
    }
    case 3:
    {
          unsigned long pos = 150;
        
          unsigned long count = 150;
        
          int _len_p_out0 = 22500;
          float * p_out = (float *) malloc(_len_p_out0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_out0; _i0++) {
            p_out[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          int _len_p_in0 = 22500;
          float * p_in = (float *) malloc(_len_p_in0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_in0; _i0++) {
            p_in[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          mix_audio(p_out,p_in,pos,count);
          free(p_out);
          free(p_in);
        
        break;
    }
    case 4:
    {
          unsigned long pos = 200;
        
          unsigned long count = 200;
        
          int _len_p_out0 = 40000;
          float * p_out = (float *) malloc(_len_p_out0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_out0; _i0++) {
            p_out[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          int _len_p_in0 = 40000;
          float * p_in = (float *) malloc(_len_p_in0*sizeof(float));
          for(int _i0 = 0; _i0 < _len_p_in0; _i0++) {
            p_in[_i0] = ((-2.0 * (next_i()%2)) + 1.0) * (-16777216.000000 + (float) next_f() / (((float) 16777215.000000/(16777215.000000 - -16777216.000000))));
          }
        
          mix_audio(p_out,p_in,pos,count);
          free(p_out);
          free(p_in);
        
        break;
    }

    default:
        usage();
        break;

    }

    return 0;
}
