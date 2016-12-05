/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.5     Thu Oct  3 11:36:14 2002 (UTC)              */
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


/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_fir_gen: FIR Filter                                            */
/*                                                                         */
/*  REVISION DATE                                                          */
/*      28-Jun-2000                                                        */
/*                                                                         */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void DSP_fir_gen                                                    */
/*      (                                                                   */
/*          const short *restrict x,  // Input ('nr + nh - 1' samples) //   */
/*          const short *restrict h,  // Filter coefficients (nh taps) //   */
/*          short       *restrict r,  // Output array ('nr' samples)   //   */
/*          int                   nh, // Length of filter (nh >= 5)    //   */
/*          int                   nr  // Length of output (nr >= 1)    //   */
/*      );                                                                  */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Computes a real FIR filter (direct-form) using coefficients         */
/*      stored in vector h. The real data input is stored in vector x.      */
/*      The filter output result is stored in vector r. This FIR            */
/*      assumes the number of filter coefficients is greater than or        */
/*      equal to 5. It operates on 16-bit data with a 32-bit                */
/*      accumulate. This routine has no memory hits regardless of where     */
/*      x, h, and r arrays are located in memory. The filter is nr          */
/*      output samples and nh coefficients. The assembly routine            */
/*      performs 4 output samples at a time.                                */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_fir_gen
(
    const short *restrict x,  /* Input array [nr+nh-1 elements] */
    const short *restrict h,  /* Coeff array [nh elements]      */
    short       *restrict r,  /* Output array [nr elements]     */
    int nh,                   /* Number of coefficients.        */
    int nr                    /* Number of output samples.      */
)
{
    int i, j, sum;

    for (j = 0; j < nr; j++)
    {
        sum = 0;
        for (i = 0; i < nh; i++)
            sum += x[i + j] * h[i];
        r[j] = sum >> 15;
    }
}

/* ======================================================================== */
/*  End of file:  dsp_fir_gen.c                                             */
