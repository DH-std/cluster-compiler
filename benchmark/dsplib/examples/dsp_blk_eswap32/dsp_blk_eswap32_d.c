/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_blk_eswap32_d.c -- Example file for DSP_blk_eswap32             */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_blk_eswap32 function. All inputs to the function contain        */
/*      random data. The assembly version of DSP_blk_eswap32 is called      */
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
#include "DSP_blk_eswap32.h"    

/* Header file for the C function */
void DSP_blk_eswap32_c(void * x, void * r, int nx);

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
     0x5A90CAD1,  0xC5D3EB02,  0xDF70446B,  0x2D58237E,
     0x7B2EA87B,  0xB08BEB4C,  0xA02C0379,  0x63650879,
     0x2972AA59,  0x6DF31315,  0x35CDDC61,  0xB1E7435B,
     0x4D2B77CF,  0xBF8A5D83,  0x9862FB74,  0xAE98DFAA,
     0xDB191597,  0x003766B9,  0xE500B631,  0xE88FA17D,
     0x89020137,  0xBD8B72C3,  0x425421D4,  0x3253A640,
     0x58FD2FB1,  0xE99523C9,  0xB12CD65B,  0xA161DB63,
     0x506EB30D,  0x7E0C65B3,  0x85EA873F,  0x79861A5D,
     0x155FA10D,  0x555FFADB,  0x18AD3E3C,  0x4D88C3C5,
     0x4B322454,  0x134E7F8C,  0x3A41952E,  0xC2BFA09E,
     0x3BD00F85,  0xB50C3A94,  0x4B95F9F4,  0xD58F5828,
     0xCF9073E6,  0xF008463F,  0x2BA465DB,  0x60DA7AC7,
     0x8B5C677D,  0x007B0C9E,  0xB6ECD9CA,  0x1354A6B7,
     0x70FCC62C,  0x8B0E0DEC,  0x208E9186,  0xAF3B3A2A,
     0xB3B5B759,  0xB49C8DE9,  0xD61EBCDF,  0x0CE1C0C6,
     0x2795482E,  0x7161ED0A,  0xBF9A4F88,  0x8CDD62D1,
     0x2B14EDA5,  0xD7DB12E9,  0x887AEBE0,  0x8D80A15E,
     0x0DDAE964,  0xCFD5DB3F,  0xDCEBA9F8,  0x0B18627C,
     0x04E4E3ED,  0x61FAA525,  0x93C39E66,  0xA0A51197,
     0xDFBB8371,  0xE19C8B2A,  0x846CA06B,  0x013E7174,
     0x95928382,  0x5EE3AE4D,  0x4397917E,  0x26842518,
     0x50BA84F4,  0x9918D816,  0xA23B2D74,  0x5396E3CC,
     0x52164536,  0x30F9C6F0,  0x16DFFF91,  0x02610211,
     0x9B453EA5,  0x1A13C5C4,  0x3FC6031B,  0xEC8BB90B,
     0xB3B241CB,  0x1CCFDFC4,  0x0D9D646A,  0x7A0FD716
};

unsigned  r_asm[NX];
unsigned  r_c[NX];


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_blk_eswap32(x, r_asm, NX);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_blk_eswap32_c(x, r_c, NX);

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
/*  End of file:  dsp_blk_eswap32_d.c                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
