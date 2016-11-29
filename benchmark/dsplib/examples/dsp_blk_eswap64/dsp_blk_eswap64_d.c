/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_blk_eswap64_d.c -- Example file for DSP_blk_eswap64             */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_blk_eswap64 function. All inputs to the function contain        */
/*      random data. The assembly version of DSP_blk_eswap64 is called      */
/*      and the output is compared with the reference C code using          */
/*      mem_compare() in support.c.                                         */
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
#include "DSP_blk_eswap64.h"    

/* Header file for the C function */
void DSP_blk_eswap64_c(void * x, void * r, int nx);

/* ======================================================================== */
/*  DSPLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x DSP Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(x, 8);
#pragma DATA_ALIGN(r_asm, 8);
#pragma DATA_ALIGN(r_c, 8);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NX   (100)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
unsigned  x[NX] = 
{
     0x14ED8BA2,  0xA99BA6F1,  0x2AC040DC,  0x807F4FF4,
     0x1919F3A3,  0xD1F5357F,  0xDEF17902,  0xE2FC13C8,
     0x09E1F34D,  0xE31DDCD9,  0x264E2F48,  0xCFAB7686,
     0xFA4295FB,  0x9206D731,  0x61E5AF7C,  0x9D82F353,
     0x86545433,  0xA6CA4D58,  0xEBE36546,  0x20F1C85A,
     0x60208FA6,  0xAB11430D,  0x2FC36F35,  0x90D52385,
     0xDBCE4A13,  0x93964439,  0x75C05F0F,  0xA11C3D6D,
     0x34D4141D,  0x6AE68A9E,  0x68B5F414,  0x52A99336,
     0x49410582,  0x2C063AC6,  0x2E77FBA0,  0xEA442D51,
     0x31320B4D,  0xCC10F62F,  0xD1F1D48F,  0xE7641D8F,
     0x33F1F9C7,  0x41CB2538,  0x2619058A,  0xEF1CB000,
     0x932A3AEB,  0x0EDDE97B,  0x9BD06400,  0xC3619B87,
     0x0A097F9A,  0x16C7E2A0,  0xE91A853E,  0xADF6E804,
     0x275D8655,  0xB2480BB3,  0x39018E52,  0x6DAA4C0C,
     0xA830EE41,  0x4F807441,  0x9E6B88A7,  0x82976340,
     0x077DBFCB,  0xFF49F422,  0x079CF780,  0x978D55F9,
     0x38CEA35F,  0xDA576ECD,  0x959B05C3,  0xF95C62BF,
     0xD3F02368,  0xF2D4E497,  0x62B53A9E,  0x82F5AAD9,
     0x09235977,  0x3E219DFE,  0x2515EDEC,  0x6328285E,
     0xC1C34F03,  0x0E9951B1,  0x7CBF1B02,  0x3086CC83,
     0x477D9157,  0xA5CBD5B6,  0x862D454D,  0x9B04E191,
     0x76B6AD2A,  0x762EF71F,  0xC726852E,  0x551E0D25,
     0xD926587C,  0x096BEFB8,  0xCA37ADA7,  0x5678CDA1,
     0x1F7C9166,  0xC5847FEB,  0xFF8B60A9,  0xFF9803B2,
     0x4C94A228,  0xA6C313FF,  0x7701A448,  0xB20BA3D4
};

unsigned  r_asm[NX];
unsigned  r_c[NX];


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_blk_eswap64(x, r_asm, NX/2);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_blk_eswap64_c(x, r_c, NX/2);

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
/*  End of file:  dsp_blk_eswap64_d.c                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
