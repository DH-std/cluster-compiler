/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_blk_move_d.c -- Example file for DSP_blk_move                   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_blk_move function. All inputs to the function contain random    */
/*      data. The assembly version of DSP_blk_move is called and the        */
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
#include "DSP_blk_move.h"    

/* Header file for the C function */
void DSP_blk_move_c(short * x, short * r, int nx);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NX   (64)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int    test = 0;
short  x[NX] = 
{
     0x2224, -0x0CAA,  0x39B7, -0x4348, -0x569E,  0x635D, -0x29ED, -0x679F,
     0x0202,  0x4C93, -0x2FE2, -0x3B83, -0x0754,  0x0C48, -0x3E5A, -0x294B,
    -0x1CE8,  0x5F31, -0x6FAB,  0x1931, -0x242E, -0x272B, -0x285F,  0x0FD5,
    -0x778E,  0x4BE9, -0x0D97,  0x2277, -0x5888, -0x2076, -0x4D51,  0x062B,
    -0x6D5F, -0x6BF3,  0x6D9D, -0x4F2B,  0x7E7B, -0x02B5,  0x285E, -0x67C3,
    -0x7EA2, -0x5984, -0x1308, -0x45A5,  0x2EEA,  0x5D12, -0x537B,  0x6299,
     0x2790, -0x2D3C, -0x61AD, -0x7A5C,  0x2FEE,  0x335D, -0x7989, -0x36FE,
     0x5D1B, -0x3188, -0x29AE,  0x4F87,  0x0B47, -0x4E41, -0x6623,  0x3E34
};

short  r_asm[NX];
short  r_c[NX];


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_blk_move(x, r_asm, NX);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_blk_move_c(x, r_c, NX);

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
/*  End of file:  dsp_blk_move_d.c                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
