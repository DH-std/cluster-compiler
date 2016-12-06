/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_minval_d.c -- Example file for DSP_minval                       */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_minval function. All inputs to the function contain random      */
/*      data. The assembly version of DSP_minval is called and the output   */
/*      is compared with the reference C code using mem_compare() in        */
/*      support.c.                                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
    
#include <stdio.h> 
#include <stdlib.h>


/* Header file for the DSPLIB function */
#include "DSP_minval.h"    
#include "support.h"

/* Header file for the C function */
short DSP_minval_c(const short * x, int nx);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define N    (64)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const short  x[N] = 
{
    -0x00ED, -0x0014,  0x00CF, -0x0011,  0x00C9, -0x0379, -0x0173,  0x0384,
    -0x033B, -0x0127, -0x0132,  0x00B1, -0x039F, -0x0068,  0x01D7,  0x01A4,
     0x0287, -0x0004, -0x01E0,  0x0052,  0x00AC, -0x0127,  0x0295, -0x005B,
    -0x006D, -0x02F6,  0x01E5, -0x01D2,  0x02D5,  0x005A, -0x00E1,  0x02C2,
     0x00FF,  0x0393, -0x02FE, -0x018C,  0x010C,  0x018B,  0x018B, -0x02E2,
     0x01B6,  0x0032, -0x016C, -0x0137,  0x01BD, -0x01F2, -0x019C, -0x02AD,
    -0x00A5, -0x02D3, -0x0255,  0x0009, -0x01C0,  0x026F,  0x020A, -0x025C,
     0x02A0,  0x0141, -0x02F9, -0x01CE,  0x01DD,  0x03AC, -0x011E, -0x0343
};



/* ======================================================================== */
/*  Variables to catch return values from function.                         */
/* ======================================================================== */
short ret_val_asm = 0;
short ret_val_c = 0;

int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */  
    settime(); 
    ret_val_asm = DSP_minval(x, N);
    gettime();
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    ret_val_c = DSP_minval_c(x, N);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */

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
/*  End of file:  dsp_minval_d.c                                            */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
