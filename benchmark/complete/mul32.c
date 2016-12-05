/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.3     Fri Mar 29 19:26:26 2002 (UTC)              */
/*      Snapshot date:  23-Oct-2003                                         */
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
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_mul32                                                           */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      14-May-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void DSP_mul32                                                  */
/*          (                                                               */
/*              const int    *x,   // Input array of length nx  //          */
/*              const int    *y,   // Input array of length nx  //          */
/*              int *restrict r,   // Output array of length nx //          */
/*              int           nx   // Number of elements.       //          */
/*          );                                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine performs a 32-bit by 32-bit multiply, returning the    */
/*      upper 32 bits of the 64-bit result.  This is equivalent to a        */
/*      Q31 x Q31 multiply, yielding a Q30 result.                          */
/*                                                                          */
/*      The 32 x 32 multiply is constructed from 16 x 16 multiplies.        */
/*      For efficiency reasons, the 'lo * lo' term of the 32 x 32           */
/*      multiply is omitted, as it has minimal impact on the final          */
/*      result.  This is due to the fact that the 'lo * lo' term            */
/*      primarily affects the lower 32 bits of the result, and these        */
/*      are not returned.  Due to this omission, the results of this        */
/*      function differ from the exact results of a 32 x 32 multiply by     */
/*      at most 1.                                                          */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      This function is ENDIAN NEUTRAL.                                    */
/*                                                                          */
/*  NOTES                                                                   */
/*      The 32x32 multiply is an approximation, as described above.         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_mul32
(
    const int    *x,
    const int    *y,
    int *restrict r,
    int           nx
)
{
    int i;

    for (i = 0; i < nx; i++)
    {
        short           a_hi, b_hi;
        unsigned short  a_lo, b_lo;
        int             hihi, lohi, hilo, hllh;

        /* ---------------------------------------------------------------- */
        /*  A full 32x32 multiply can be constructed from four 16x16        */
        /*  multiplies.  If you divide the two 32-bit multipliers into hi   */
        /*  and lo halves, then the 32x32 product is constructed from the   */
        /*  sum of 'hi * hi', 'hi * lo', 'lo * hi', and 'lo * lo', each     */
        /*  shifted appropriately.  The 'hi' terms are signed terms, and    */
        /*  the 'lo' terms are unsigned.                                    */
        /* ---------------------------------------------------------------- */
        a_hi = (short)(x[i] >> 16);
        b_hi = (short)(y[i] >> 16);
        a_lo = (unsigned short)x[i];
        b_lo = (unsigned short)y[i];

        /* ---------------------------------------------------------------- */
        /*  For our result alignment, the 'hi * hi' term requires no shift. */
        /* ---------------------------------------------------------------- */
        hihi = a_hi * b_hi;

        /* ---------------------------------------------------------------- */
        /*  The 'lo * hi' and the 'hi * lo' terms will both be shifted      */
        /*  right by 16.  Therefore, we will compute them, then add them    */
        /*  together.  Note that this sum can be 33 bits long, and we need  */
        /*  the upper 17 bits of that 33-bit sum.  Hence, we use longs.     */
        /* ---------------------------------------------------------------- */
        hilo = a_hi * b_lo;
        lohi = a_lo * b_hi;
        hllh = (hilo + (long)lohi) >> 16;

        /* ---------------------------------------------------------------- */
        /*  Merge the middle and upper sums to form the final result.       */
        /* ---------------------------------------------------------------- */
        r[i] = hihi + hllh;
    }
}
/* ======================================================================== */
/*  End of file:  dsp_mul32.c                                               */
