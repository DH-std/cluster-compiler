/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      pix_expand                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void pix_expand                                                     */
/*      (                                                                   */
/*          int n,                                    // # of elements //   */
/*          const unsigned char *restrict in_data,    // Input data    //   */
/*          short               *restrict out_data    // Output data   //   */
/*      )                                                                   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Reads an array of unsigned 8-bit values and store them to a         */
/*      16-bit array.  This step is often used as the first step            */
/*      when processing pixels or other low-precision data at 16-bit        */
/*      intermediate precision.                                             */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#pragma CODE_SECTION(pix_expand_c,   ".text:intrinsic");
static const char Copyright[] = "Copyright (c) 2000 Texas Instruments "
                                "Incorporated.  All Rights Reserved.";

void pix_expand_c
(   
    int n,
    const unsigned char *restrict in_data,
    short               *restrict out_data
)
{   
    int i;

    _nassert((int) in_data  % 8 == 0);
    _nassert((int) out_data % 8 == 0);
    #pragma MUST_ITERATE(16,,16);
    #pragma UNROLL(16);
    for (i = 0; i < n; i++)
        out_data[i] =  in_data[i];
}

/* ======================================================================== */
/*  End of file:  pix_expand_i.c                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
