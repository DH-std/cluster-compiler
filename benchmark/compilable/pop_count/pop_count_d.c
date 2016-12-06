
#include <stdio.h> 
#include <stdlib.h>

/* Header file for the DSPLIB function */
#include "pop_count.h"
#include "support.h"   

/* Header file for the C function */
unsigned popCnt(unsigned input);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define N    (4200067296)
unsigned ret_val_asm = 0;
unsigned ret_val_c = 0;

int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    settime();
    ret_val_asm = popCnt(N);
    gettime();
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    ret_val_c = popCnt_c(N);



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
/*  End of file:  dsp_maxval_d.c                                            */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
