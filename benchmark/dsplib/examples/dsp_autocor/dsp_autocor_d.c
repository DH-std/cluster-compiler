/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_autocor_d.c -- Example file for DSP_autocor                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_autocor function. All inputs to the function contain random     */
/*      data. The assembly version of DSP_autocor is called and the         */
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
#include "DSP_autocor.h"    

/* Header file for the C function */
void DSP_autocor_c(short * r, const short * x, int nx, int nr);

/* ======================================================================== */
/*  DSPLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x DSP Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(x, 8);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NR       (16)
#define NX       (40)
#define NXPNR    (56)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
short  r_asm[NR];
short  r_c[NR];

const short  x[NXPNR] = 
{
    -0x3C62, -0x47B4,  0x4B74,  0x41E5, -0x611A, -0x1578, -0x73C0, -0x4395,
     0x1749, -0x43BD,  0x2D2F,  0x7812,  0x4CEB,  0x017B,  0x4BB0,  0x7DEF,
     0x2A9C, -0x1883, -0x597E, -0x7CB4,  0x7084,  0x13FC,  0x3C1F,  0x2410,
     0x22A4, -0x1061, -0x0DC1,  0x4A1E,  0x7546, -0x684B, -0x2B85,  0x3E67,
     0x14E1, -0x0570, -0x65D1, -0x2B4A,  0x5AF4, -0x5CD6, -0x4B45,  0x5424,
     0x34C2,  0x78DE, -0x17D3,  0x22BB,  0x4BD5,  0x4774,  0x7F5F,  0x2CAE,
    -0x767F,  0x7762, -0x512B,  0x6892,  0x57F6,  0x23A1, -0x7246,  0x698B
};



int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_autocor(r_asm, x, NX, NR);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_autocor_c(r_c, x, NX, NR);

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
/*  End of file:  dsp_autocor_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
