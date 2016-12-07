/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_q15tofl_d.c -- Example file for DSP_q15tofl                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB DSP_q15   */
/*      tofl function. All inputs to the function contain random data.      */
/*      The assembly version of DSP_q15tofl is called and the output is     */
/*      compared with the reference C code using mem_compare() in           */
/*      support.c.                                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
    
#include <stdio.h> 
#include <stdlib.h>


/* Header file for the DSPLIB function */
#include "DSP_q15tofl.h"
#include "support.h"

/* Header file for the C function */
void DSP_q15tofl_c(short * x, float * r, int nx);


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
    -0x6738,  0x64CD, -0x0883, -0x0191, -0x6A07,  0x63B6,  0x04A6, -0x2F44,
    -0x1E47,  0x2008, -0x1E8D,  0x53E8, -0x0AFE,  0x5524,  0x6B57,  0x20A5,
    -0x3EA2,  0x4F39, -0x6E51, -0x0014
};

float  r_asm[NX];
float  r_c[NX];


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */
    settime();   
    DSP_q15tofl(x, r_asm, NX);
    gettime();
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_q15tofl_c(x, r_c, NX);

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
/*  End of file:  dsp_q15tofl_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
