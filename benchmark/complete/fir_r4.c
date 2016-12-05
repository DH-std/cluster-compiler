/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.2     Wed Oct  4 17:44:01 2000 (UTC)              */
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
/*      DSP_fir_r4: FIR Filter (radix 4)                                    */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      04-Oct-2000                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void DSP_fir_r4                                                     */
/*      (                                                                   */
/*          const short *restrict x,  // Input array [nr+nh-1 elements] //  */
/*          const short *restrict h,  // Coeff array [nh elements]      //  */
/*          short       *restrict r,  // Output array [nr elements]     //  */
/*          int nh,                   // Number of coefficients.        //  */
/*          int nr                    // Number of output samples.      //  */
/*      )                                                                   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Computes a real FIR filter (direct-form) using coefficients         */
/*      stored in vector h.  The real data input is stored in vector x.     */
/*      The filter output result is stored in vector r.  Input data and     */
/*      filter taps are 16-bit, with intermediate values kept at 32-bit     */
/*      precision.  Filter taps are expected in Q15 format.                 */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      n/a                                                                 */
/*                                                                          */
/*  NOTES                                                                   */
/*      n/a                                                                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_fir_r4
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
/*  End of file:  dsp_fir_r4.c                                              */
