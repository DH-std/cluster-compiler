/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.4     Thu Mar  8 18:26:11 2001 (UTC)              */
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
/*      DSP_fir_r8: FIR Filter (radix 8)                                    */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      04-Oct-2000                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void DSP_fir_r8                                                     */
/*      (                                                                   */
/*          const short *restrict x,  // Input array [nr+nh-1 elements] //  */
/*          const short *restrict h,  // Coeff array [nh elements]      //  */
/*          short       *restrict r,  // Output array [nr elements]     //  */
/*          short nh,                 // Number of coefficients.        //  */
/*          short nr                  // Number of output samples.      //  */
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

void DSP_fir_r8
(
    const short *restrict x,  /* Input array [nr+nh-1 elements] */
    const short *restrict h,  /* Coeff array [nh elements]      */
    short       *restrict r,  /* Output array [nr elements]     */
    short nh,                 /* Number of coefficients.        */
    short nr                  /* Number of output samples.      */
)
{
    int i, j, sum;

     /*-------------------------------------------------------------------*/
     /* The following assumptions are made if NOASSUME is not defined     */
     /* It is assumed that the number of output samples >= 2. It is also  */
     /* assumed that the number of output samples to be computed is a     */
     /* multiple of 2. In addition it is assumed, that the number of      */
     /* filter taps is >= 4, and a multiple of 4.                         */
     /*-------------------------------------------------------------------*/

     #ifndef NOASSUME
    _nassert(nr >= 2);
    _nassert(nr % 2 == 0);
    _nassert(nh >= 4);
    _nassert(nh % 4 == 0);
    #pragma MUST_ITERATE(4,,4);
    #endif

    for (j = 0; j < nr; j++)
    {

        /*----------------------------------------------------------------*/
        /* Initizlize accumulator for FIR sum to be zero.                 */
        /*----------------------------------------------------------------*/

        sum = 0;

        /*----------------------------------------------------------------*/
        /* The following assumptions are made if noassume is defined.     */
        /* It is assumed that the input, filter and output pointers       */
        /* are dword aligned. In addition it is assumed that the #        */
        /* of filter taps is at least 8, or a multiple of 8.              */
        /*----------------------------------------------------------------*/

        #ifndef NOASSUME
        _nassert((int)x % 8 == 0);
        _nassert((int)h % 8 == 0);
        _nassert((int)r % 8 == 0);
        #pragma MUST_ITERATE(8,,8);
        #endif

        /*---------------------------------------------------------------*/
        /* Compute FIR as sum of products.                               */
        /*---------------------------------------------------------------*/

        for (i = 0; i < nh; i++)
        {
            sum += x[i + j] * h[i];
        }

        /*---------------------------------------------------------------*/
        /* Shift out FIR sum and store out.                              */
        /*---------------------------------------------------------------*/

        r[j] = sum >> 15;
    }
}

/* ======================================================================== */
/*  End of file:  dsp_fir_r8.c                                              */
