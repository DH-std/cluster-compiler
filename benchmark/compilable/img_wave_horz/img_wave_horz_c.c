/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
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
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


/* ======================================================================== */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_wave_horz                                                       */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      15-Oct-2000                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      i_data  = input row of data                                         */
/*      lp_filt = Low-pass quadrature mirror filter                         */
/*      hp_filt = High-pass quadrature mirror filter                        */
/*      o_data  = output row of detailed/reference decimated outputs        */
/*      x_dim   = width of the input row                                    */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This kernel performs a 1D Periodic Orthogonal Wavelet               */
/*      decomposition.  This also performs athe row decomposition in a      */
/*      2D wavelet transform.  An in put signal x[n] is first low pass      */
/*      and high pass filterd and decimated by two.  This results in a      */
/*      reference signal r1[n] which is the decimated output obtained       */
/*      by dropping the odd samples of the low pass filtered output and     */
/*      a detail signal d[n] obtained by dropping the odd samples of        */
/*      the high-pass output.  A circular convolution algorithm is          */
/*      implemented and hence the wavelet transform is periodic.  The       */
/*      reference signal and the detail signal are half the size of the     */
/*      original signal.  The reference signal may then be iterated         */
/*      again to perform another scale of multi-resolution analysis.        */
/*                                                                          */
/*  BIBLIOGRAPHY                                                            */
/*      A Wavelet Tour of Signal Processing Stephane' Mallat. Academic      */
/*      Press                                                               */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2002 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void IMG_wave_horz_c
(
    const short *restrict i_data,    /* Row of input pixels  */
    const short *restrict lp_filt,   /* Low-pass QMF filter  */
    const short *restrict hp_filt,   /* High-pass QMF filter */
    short       *restrict o_data,    /* Row of output data   */
    int                   x_dim      /* Length of input.     */
)
{
    int i, j;

    for (i = 0; i < x_dim; i += 2)
    {
        int lp_sum = 1 << 14;

        for (j = 0; j < 8; j++)
            lp_sum += i_data[(i + j) % x_dim] * lp_filt[j];

        o_data[i >> 1] = lp_sum >> 15;
    }

    for (i = 0; i < x_dim; i += 2)
    {
        int hp_sum = 1 << 14;

        for (j = 0; j < 8; j++)
            hp_sum += i_data[(i + x_dim - 6 + j) % x_dim] * hp_filt[7 - j];

        o_data[(i + x_dim) >> 1] = hp_sum >> 15;
    }
}
/* ======================================================================== */
/*  End of file:  img_wave_horz.c                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2002 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
