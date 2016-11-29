/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_fir_cplx_d.c -- Example file for DSP_fir_cplx                   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_fir_cplx function. All inputs to the function contain random    */
/*      data. The assembly version of DSP_fir_cplx is called and the        */
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
#include "DSP_fir_cplx.h"    

/* Header file for the C function */
void DSP_fir_cplx_c(const short * x, const short * h, short * r, int nh, int nr);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NH   (10)
#define NH2  (20)
#define NR   (20)
#define NR2  (40)
#define NX   (58)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const short  x[NX] = 
{
     0x2D98, -0x074B,  0x68EE, -0x2D98,  0x59B7, -0x247B, -0x4333,  0x1DBB,
    -0x63AA,  0x1C1F, -0x005E,  0x08AA,  0x6321, -0x1FBC, -0x4417,  0x7B0D,
    -0x1CEA, -0x2208, -0x30DF, -0x2FF6, -0x470D, -0x350C,  0x5319, -0x3553,
    -0x7996,  0x0A3D, -0x3B26,  0x6A74, -0x6322, -0x564E,  0x47DF, -0x6259,
    -0x4E4C, -0x1FE0, -0x5DC6, -0x0865,  0x7385,  0x34AF,  0x7A8F, -0x63F3,
    -0x546E,  0x1891, -0x1E99,  0x200B, -0x25F1, -0x66B9,  0x63A3, -0x26DE,
     0x5033, -0x0F78,  0x56F7, -0x51C7,  0x6812,  0x054A, -0x1AAD,  0x0243,
     0x37F1,  0x37EB
};

const short  h[NH2] = 
{
     0x6D1B,  0x18A4,  0x489F, -0x1B14,  0x3167,  0x53DF, -0x5F2B, -0x647F,
     0x161B, -0x3C81, -0x5840, -0x2A70,  0x51B0,  0x0282, -0x68CC, -0x667C,
     0x3317,  0x496E,  0x2895, -0x414F
};

short  r_asm[NR2];
short  r_c[NR2];



int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/*  Note that x should point to x[2*(NH-1)].                                */
/* ======================================================================== */   
    DSP_fir_cplx(x+2*(NH-1), h, r_asm, NH, NR);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/*  Note that x should point to x[2*[NH-1)].                                */
/* ======================================================================== */
    DSP_fir_cplx_c(x+2*(NH-1), h, r_c, NH, NR);

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
/*  End of file:  dsp_fir_cplx_d.c                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
