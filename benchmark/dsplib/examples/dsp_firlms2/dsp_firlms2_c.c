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
/*  NAME                                                                    */
/*      DSP_firlms2 -- Least Mean Square Adaptive Filter                    */
/*                 Natural C Implementation                                 */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      13-Mar-2002                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*                                                                          */
/*      This routine has the following C prototype:                         */
/*                                                                          */
/*          long DSP_firlms2                                                */
/*          (                                                               */
/*              short       *restrict h,  // Filter Coefficients            */
/*              const short *restrict x,  // Input Data                     */
/*              short                 b,  // Error from previous FIR        */
/*              int                   nh, // Number of Coefficients         */
/*          )                                                               */
/*                                                                          */
/*      The DSP_firlms2 routine accepts a list of 'nh' input data and 'nh'  */
/*      adaptive filter coefficients and updates the coefficients by        */
/*      adding weighted error times the inputs to the original              */
/*      coefficients. This assumes single sample input followed by the      */
/*      last nh-1 inputs and nh coefficients.                               */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*      The algorithm is simple and is implemented as follows:              */
/*                                                                          */
/*          long DSP_firlms2                                                */
/*          (                                                               */
/*              short       *restrict h,  // Filter Coefficients            */
/*              const short *restrict x,  // Input Data                     */
/*              short                 b,  // Error from previous FIR        */
/*              int                   nh, // Number of Coefficients         */
/*          )                                                               */
/*                                                                          */
/*          {                                                               */
/*              int  i;                                                     */
/*              long r=0;                                                   */
/*                                                                          */
/*              for(i = 0; i < nh; i++)                                     */
/*              {                                                           */
/*                * Update the filter coefficients *                        */
/*                                                                          */
/*                  h[i] += (x[i] * b) >> 15;                               */
/*                                                                          */
/*                * Calculate the filter output    *                        */
/*                                                                          */
/*                  r    += x[i + 1] * h[i];                                */
/*              }                                                           */
/*              return r;                                                   */
/*          }                                                               */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*                                                                          */
/*      - Assumes 16-bit input data, error and filter coefficients.         */
/*      - nh > = 4 and is a multiple of 4                                   */
/*                                                                          */
/*  SOURCE                                                                  */
/*                                                                          */
/*      DSPLIB                                                              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

long DSP_firlms2_c
(
    short *restrict h,         // h[nh] = Coefficient Array
    const short *restrict x,   // x[nh] = Input Array
    short b,                   // b = Error from Previous FIR
    int nh                     // nh = Number of Coefficients
)

{

    int       i;
    long  r = 0; // r is output of the filter

    for (i = 0; i < nh; i++)
    {
        h[i] += (x[i] * b) >> 15;
        r    += x[i+1] * h[i];
    }

    return r;
}

/* ======================================================================== */
/*  End of file:  dsp_firlms2.c                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
