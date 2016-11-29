/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_blk_eswap16_d.c -- Example file for DSP_blk_eswap16             */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_blk_eswap16 function. All inputs to the function contain        */
/*      random data. The assembly version of DSP_blk_eswap16 is called      */
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
#include "DSP_blk_eswap16.h"    

/* Header file for the C function */
void DSP_blk_eswap16_c(void * x, void * r, int nx);

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
#define NX   (200)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
unsigned short  x[NX] = 
{
     0xE33E,  0xEE1A,  0x91C0,  0x8DBA,  0xB8FA,  0xF3C0,  0x2FE6,  0x7A10,
     0x3314,  0x287F,  0x1523,  0x1F0E,  0x6438,  0xC9DF,  0x64C1,  0x7A7B,
     0x2E9C,  0x4441,  0x01FD,  0x2491,  0x17A4,  0x0D7E,  0x701C,  0xF752,
     0x17C5,  0xE5AC,  0x7F68,  0x391A,  0xC464,  0xCB9B,  0x605D,  0xDB90,
     0x2BD9,  0xC87A,  0xA247,  0x785E,  0x74F2,  0xC838,  0x6FA6,  0xF030,
     0x5F62,  0x7360,  0xD991,  0xC8CC,  0xBFCB,  0x9894,  0x4159,  0x8135,
     0x624B,  0x238A,  0x73DE,  0x6BA5,  0x3BC3,  0xA7C7,  0xA82A,  0x25C6,
     0x9175,  0xF600,  0xF29E,  0xC26B,  0x01AE,  0x3C4C,  0xC999,  0x7A91,
     0xED80,  0xA24E,  0x56E8,  0xF510,  0x43C1,  0x6DAA,  0x1E67,  0xAC74,
     0x85E7,  0xFD17,  0x1FD4,  0xF781,  0x28D0,  0x7977,  0xC35D,  0x4A74,
     0x3FB9,  0xD52A,  0xEC2D,  0x2754,  0x0019,  0xDD23,  0xD3CB,  0x6190,
     0x508E,  0x5986,  0x9CB3,  0x0CB6,  0x2FCA,  0xB8B4,  0xEA29,  0xBE54,
     0x3935,  0x5654,  0xA12D,  0xBF06,  0x15F1,  0xBB36,  0xE9AC,  0x039D,
     0xA5D9,  0x2027,  0xC964,  0x11C3,  0xA8AB,  0x05FB,  0xE702,  0x7C4E,
     0x09F2,  0xD206,  0x0C68,  0xF7FE,  0x60CE,  0xB109,  0xEE02,  0xAE66,
     0x926C,  0xFEA9,  0x15A5,  0x83BC,  0x8644,  0xD2D3,  0x5DF3,  0x2D4B,
     0x62E6,  0x7A02,  0x28FB,  0x7F35,  0x126F,  0xE74C,  0x17D4,  0xB6C5,
     0xF7BC,  0x39A9,  0xA96B,  0xCB53,  0xA9CC,  0x6BA8,  0x8D40,  0x54AA,
     0x0EDD,  0x840C,  0x08EB,  0xCD4B,  0x82F2,  0x689C,  0x64C5,  0x1F08,
     0x3810,  0x0D41,  0x21BB,  0x7CB7,  0x78BC,  0x58CD,  0x13BB,  0x46F4,
     0xF374,  0x5E37,  0xF9BA,  0x3316,  0xB62E,  0x9C1C,  0xF974,  0x2B39,
     0xF064,  0x4898,  0xE576,  0xEA41,  0x2306,  0x20FD,  0xB21C,  0xC284,
     0xFAE7,  0xB61D,  0x4724,  0x68EF,  0xCFA5,  0x7F9B,  0x1D8C,  0xC4A9,
     0xBA19,  0x4326,  0xF914,  0xDA17,  0x6715,  0x2166,  0x4363,  0x2538,
     0x87A1,  0x837B,  0x172A,  0x6398,  0xF179,  0x591E,  0xB6C4,  0xB597
};

unsigned short  r_asm[NX];
unsigned short  r_c[NX];


int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_blk_eswap16(x, r_asm, NX);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_blk_eswap16_c(x, r_c, NX);

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
/*  End of file:  dsp_blk_eswap16_d.c                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
