/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_fltoq15_d.c -- Example file for DSP_fltoq15                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_fltoq15 function. All inputs to the function contain random     */
/*      data. The assembly version of DSP_fltoq15 is called and the         */
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
#include "DSP_fltoq15.h"    

/* Header file for the C function */
void DSP_fltoq15_c(float * x, short * r, short nx);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NX   (20)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
float  x[NX] = 
{
    - 0.9496202,   0.9389323,   0.6501744,   0.9890941,
    - 0.6149895,   0.1934405, - 0.0888628, - 0.1593419,
      0.9673895,   0.0888673,   0.4763519,   0.1117054,
    - 0.4901115,   0.7792529, - 0.9710504, - 0.6598921,
      0.3299095, - 0.3781488,   0.9893967,   0.9076802
};

short  r_asm[NX];
short  r_c[NX];


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_fltoq15(x, r_asm, NX);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_fltoq15_c(x, r_c, NX);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(r_asm, "r_asm", r_c, "r_c", sizeof(r_c));
    if (test == 0) 
    {
      printf("r_asm vs. r_c");
      printf("\nVerification successful.\n");
    }

}

/* ======================================================================== */
/*  End of file:  dsp_fltoq15_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
