/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_recip16_d.c -- Example file for DSP_recip16                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_recip16 function. All inputs to the function contain random     */
/*      data. The assembly version of DSP_recip16 is called and the         */
/*      output is compared with the reference C code using mem_compare()    */
/*      in support.c.                                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
    
#include <stdio.h> 
#include <stdlib.h>

/* Header file for the memory compare function */
int mem_compare(const void *ptr1, const char *name1, 
                const void *ptr2, const char *name2, int len);

/* Header file for the DSPLIB function */
#include "DSP_recip16.h"    

/* Header file for the C function */
void DSP_recip16_c(short * x, short * rfrac, short * rexp, short nx);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NX   (20)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
short  x[NX] = 
{
     0x2071,  0x7087,  0x1F7F,  0x77C3, -0x70FF, -0x16F4,  0x2058,  0x6218,
     0x0A65, -0x5835, -0x5403,  0x7D40,  0x4AE8, -0x0930,  0x0F53, -0x5DC3,
     0x0DC6,  0x7CD2,  0x06B8,  0x2E0B
};

short  rfrac_asm[NX];
short  rfrac_c[NX];

short  rexp_asm[NX];
short  rexp_c[NX];


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_recip16(x, rfrac_asm, rexp_asm, NX);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_recip16_c(x, rfrac_c, rexp_c, NX);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(rfrac_asm, "rfrac_asm", rfrac_c, "rfrac_c", sizeof(rfrac_c));
    if (test == 0) 
    {
      printf("rfrac_asm vs. rfrac_c");
      printf("\nVerification successful.\n");
    }

    test = mem_compare(rexp_asm, "rexp_asm", rexp_c, "rexp_c", sizeof(rexp_c));
    if (test == 0) 
    {
      printf("rexp_asm vs. rexp_c");
      printf("\nVerification successful.\n");
    }

}

/* ======================================================================== */
/*  End of file:  dsp_recip16_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
