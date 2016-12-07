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


/* ======================================================================= */
/*  NAME                                                                   */
/*      DSP_fir_cplx -- Natural C code for Complex Filter.                 */
/*                                                                         */
/*  REVISION DATE                                                          */
/*      31-Oct-2000                                                        */
/*                                                                         */
/*  USAGE                                                                  */
/*      This routine is C-callable and can be called as:                   */
/*                                                                         */
/*      void DSP_fir_cplx                                                  */
/*      (                                                                  */
/*          const short *restrict x,                                       */
/*          const short *restrict h,                                       */
/*          short       *restrict r,                                       */
/*          short                 nh,                                      */
/*          short                 nr                                       */
/*     )                                                                   */
/*                                                                         */
/*     x[2*(nr+nh-1)] : Complex input data. x must point to x[2*(nh-1)].   */
/*     h[2*nh]        : Complex coefficients (in normal order).            */
/*     r[2*nr]        : Complex output data.                               */
/*     nh             : Number of complex coefficients.                    */
/*     nr             : Number of complex output samples.                  */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*      This complex FIR computes nr complex output samples using nh       */
/*      complex coefficients. It operates on 16-bit data with a 32-bit     */
/*      accumulate. Each array consists of an even and odd term with even  */
/*      terms representing the real part of the element and the odd terms  */
/*      the imaginary part. The pointer to input array x must point to the */
/*      (nh)th complex sample, i.e. element 2*(nh-1), upon entry to the    */
/*      function. The coefficients are expected in normal order.           */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================= */

void DSP_fir_cplx_c
(
    const short *restrict x,
    const short *restrict h,
    short       *restrict r,
    short nh,
    short nr
)
{
    int i,    j;
    int imag, real;


    for (i = 0; i < 2*nr; i += 2)
    {
        imag = 0;
        real = 0;
        for (j = 0; j < 2*nh; j += 2)
        {
            real += h[j+0] * x[i-j+0] - h[j+1] * x[i-j+1];
            imag += h[j+1] * x[i-j+0] + h[j+0] * x[i-j+1];
        }
        r[i  ] = (real >> 15);
        r[i+1] = (imag >> 15);
    }
}

/* ======================================================================== */
/*  End of file:  dsp_fir_cplx.c                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
