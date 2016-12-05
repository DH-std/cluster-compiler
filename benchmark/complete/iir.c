/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.4     Tue Jun 24 17:03:36 2003 (UTC)              */
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
/*      iir -- Infinite Impulse Response Filter/ ARMA filter                */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      29-Mar-2002                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable and can be called as:                    */
/*                                                                          */
/*      void DSP_iir                                                        */
/*      (                                                                   */
/*          short *restrict r1,                                             */
/*          const short *x,                                                 */
/*          short *restrict r2,                                             */
/*          const short *h2,                                                */
/*          const short *h1,                                                */
/*          int nr                                                          */
/*      )                                                                   */
/*                                                                          */
/*      r1[nr+4] : Output array (used).                                     */
/*      x[nr+4]  : Input array.                                             */
/*      r2[nr]   : Output array (stored).                                   */
/*      h1[5]    : 4 Autoregressive filter coefficients (h1[0] is not used) */
/*      h2[5]    : 5 Moving-average filter coefficients.                    */
/*      nr       : Number of output samples. Must be >= 8.                  */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The IIR performs an auto-regressive moving-average (ARMA) filter    */
/*      with 4 auto-regressive filter coefficients and 5 moving-average     */
/*      filter coefficients for nr output samples. The output vector is     */
/*      stored in two locations.  This routine is used as a high pass       */
/*      filter in the VSELP vocoder.                                        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_iir
(
    short *restrict r1,      /* Output array (used)      */
    const short     *x,      /* Input array              */
    short *restrict r2,      /* Output array (stored)    */
    const short     *h2,     /* Filter Coeffs. AR part   */
    const short     *h1,     /* Filter Coeffs. FIR part  */
    int             nr       /* Number of output samples */
)
{
    int i, j;
    int sum;

    for ( i = 0; i < nr; i++)
    {
        sum = h2[0] * x[4 + i];

        for ( j = 1; j <= 4; j++)
             sum += h2[j] * x[4 + i - j] - h1[j] * r1[4 + i - j];

        r1[4 + i] = (sum >> 15);
        r2[i]     = r1[4 + i];
    }
}

/* ======================================================================== */
/*  End of file:  dsp_iir.c                                                 */
