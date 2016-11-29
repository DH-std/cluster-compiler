/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_dotprod                                                         */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      29-Mar-2002                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          int DSP_dotprod                                                 */
/*          (                                                               */
/*              const short *m,           // First vector       //          */
/*              const short *n,           // Second vector      //          */
/*              int  count                // Length of vectors  //          */
/*          );                                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The "DSP_dotprod" function implements a vector product of two input */
/*      files, returning the result.                                        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

int DSP_dotprod_c
(
    const short *m,
    const short *n,
    int  count
)
{
    int i;
    int prod, sum = 0;

    #ifndef NOASSUME
    _nassert((int)m % 8 == 0);               /* Double-word aligned         */
    _nassert((int)n % 8 == 0);               /* Double-word aligned         */
    _nassert((int)m % 16 != (int)n % 16);    /* In different banks          */
    #pragma MUST_ITERATE(4,,4);              /* count >= 4, mult of 4       */
    #endif

    for (i = 0; i < count; i++)
    {
        prod = m[i] * n[i];
        sum += prod;
    }

    return sum;
}

/* ======================================================================== */
/*  End of file:  dsp_dotprod.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
