fir_sym.c/      1066929506  0     0     0       7167      `
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.2     Tue Mar 12 01:06:04 2002 (UTC)              */
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
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_fir_sym -- Symmetric FIR                                        */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      11-Mar-2002                                                         */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This function is C callable, and may be called as follows:          */
/*                                                                          */
/*      void DSP_fir_sym                                                    */
/*      (                                                                   */
/*          const short * x,      // Input samples                   //     */
/*          const short * h ,     // Filter taps                     //     */
/*          short * restrict r,   // Output samples                  //     */
/*          int nh,               // Number of symmetric filter taps //     */
/*          int nr,               // Number of output samples        //     */
/*          int s                 // Final output shift.             //     */
/*      );                                                                  */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This function applies a symmetric filter to the input samples.      */
/*      The filter tap array h[] provides 'nh + 1' total filter taps.       */
/*      The filter tap at h[nh] forms the center point of the filter.       */
/*      The taps at h[nh - 1] through h[0] form a symmetric filter          */
/*      about this central tap.  The effective filter length is thus        */
/*      2*nh + 1 taps.                                                      */
/*                                                                          */
/*      The filter is performed on 16-bit data with 16-bit coefficients,    */
/*      accumulating intermediate results to 40-bit precision.  The         */
/*      accumulator is rounded and truncated according to the value         */
/*      provided in 's'.  This allows a variety of Q-points to be used.     */
/*                                                                          */
/*      Note that samples are added together before multiplication, and     */
/*      so overflow *may* result for large-scale values, despite the        */
/*      40-bit accumulation.                                                */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_fir_sym
(
    const short * x,      /* Input samples                   */
    const short * h ,     /* Filter taps                     */
    short * restrict r,   /* Output samples                  */
    int nh,               /* Number of symmetric filter taps */
    int nr,               /* Number of output samples        */
    int s                 /* Final output shift.             */
)
{
    int  i, j;
    long y0, round = (long) 1 << (s - 1);

    #ifndef  NOASSUME
    _nassert((int)(x)%8 == 0);
    _nassert((int)(h)%8 == 0);
    _nassert(nh >= 8);
    _nassert((int)(nh)%8 == 0);
    #endif

    /* -------------------------------------------------------------------- */
    /*  The outer loop iterates once for each output sample.                */
    /* -------------------------------------------------------------------- */
#pragma UNROLL(2);
    for (j = 0; j < nr; j++)
    {
        y0 = round;

        /* ---------------------------------------------------------------- */
        /*  The inner loop calculates the filter for an individual sample.  */
        /* ---------------------------------------------------------------- */
#pragma UNROLL(4);
        for (i = 0; i < nh; i++)
            y0 += ((short) (x[j + i] + x[j + 2 * nh - i])) * h[i];

        y0 += x[j + nh] * h[nh];

        r[j] = (int) (y0 >> s);
    }
}

/* ======================================================================== */
/*  End of file:  dsp_fir_sym.c                                             */
