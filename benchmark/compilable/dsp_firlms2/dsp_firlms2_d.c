/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_firlms2_d.c -- Example file for DSP_firlms2                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_firlms2 function. All inputs to the function contain random     */
/*      data. The assembly version of DSP_firlms2 is called and the         */
/*      output is compared with the reference C code using mem_compare()    */
/*      in support.c.                                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
    
#include <stdio.h> 
#include <stdlib.h>


/* Header file for the DSPLIB function */
#include "DSP_firlms2.h"  
#include "support.h"  

/* Header file for the C function */
long DSP_firlms2_c(short * h, const short * x, short b, int nh);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NH   (24)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
short  h_asm[NH] = 
{
     0x6C47,  0x0AB4, -0x4B46,  0x7824, -0x63F1,  0x2EA4,  0x63D4,  0x38DA,
     0x35D4,  0x019B, -0x351F, -0x240C,  0x08FB,  0x75E0,  0x0D2A, -0x3A43,
    -0x3EFD,  0x625C, -0x2056,  0x7A38,  0x6B75, -0x21FF,  0x340E, -0x55DF
};
short  h_c[NH];

const short  x[NH] = 
{
     0x4583, -0x5655, -0x63C7, -0x08D7,  0x1007, -0x27A2,  0x0FEE, -0x7E89,
    -0x3F00, -0x2C9A, -0x25B0,  0x5066,  0x6DC1, -0x19CA,  0x280B, -0x2743,
     0x3550,  0x22E1,  0x3DC5,  0x4CD7, -0x0A84,  0x318E, -0x6D7C,  0x456B
};




/* ======================================================================== */
/*  Variables to catch return values from function.                         */
/* ======================================================================== */
long ret_val_asm = 0;
long ret_val_c = 0;

int main()
{   
/* ------------------------------------------------------------------------ */
/*  Duplicate input for natural-C function call.                            */
/* ------------------------------------------------------------------------ */
    memcpy(h_c, h_asm, sizeof(h_asm));

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */ 
    settime();  
    ret_val_asm = DSP_firlms2(h_asm, x, 123, NH);
    gettime();
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    ret_val_c = DSP_firlms2_c(h_c, x, 123, NH);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(h_asm, "h_asm", h_c, "h_c", sizeof(h_c));
    if (test == 0) 
    {
      printf("h_asm vs. h_c");
      printf("\nVerification successful.\n");
    }
      printf("ret_val_asm vs. ret_val_c");
    if ((ret_val_c == ret_val_asm)) 
    {
      printf("\nVerification successful.\n");
    } else 
    {
      printf("\nVerification failure.\n");
    }

}

/* ======================================================================== */
/*  End of file:  dsp_firlms2_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
