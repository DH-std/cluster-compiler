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


/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      IMG_corr_gen                                                       */
/*                                                                         */
/*  REVISION DATE                                                          */
/*      15-Oct-2000                                                        */
/*                                                                         */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_corr_gen                                                   */
/*      (                                                                   */
/*          short   *x,                                                     */
/*          short   *h,                                                     */
/*          short   *y,                                                     */
/*          int     m,                                                      */
/*          int     x_dim                                                   */
/*      );                                                                  */
/*                                                                          */
/*      x[]   : Input pixel array.                                          */
/*      h[M]  : Input 1xM mask array                                        */
/*      y[]   : Output array of correlation sum                             */
/*      M     : Length of filter.                                           */
/*      x_dim : Width of input image                                        */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The routine performs a generalized correlation with a 1 by M tap    */
/*      filter. It can be called repetitively to form an arbitrary MxN 2D   */
/*      generalized correlation kernel. The correlation sum is stored as    */
/*      half words. The input pixel, and mask data is assumed to come in    */
/*      as shorts.  No restrictions apply to x_dim and M.                   */
/*                                                                          */
/*      If the width of the input image is x_dim and the mask is M then     */
/*      the output array must have at-least a dimension of (x_dim - m + 8). */
/*                                                                          */
/*  C CODE                                                                  */
/*      void IMG_corr_gen(short *x, short *h, short *y, int M, int x_dim)   */
/*      {                                                                   */
/*          iters = x_dim - M;                                              */
/*          for (j = 0; j < iters; j++)                                     */
/*          {                                                               */
/*              sum =  y[j];                                                */
/*              for (i = 0; i < M; i++)                                     */
/*              {                                                           */
/*                  sum += xptr[i + j] * hptr[i];                           */
/*              }                                                           */
/*              y[j] = sum;                                                 */
/*          }                                                               */
/*      }                                                                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2002 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void IMG_corr_gen_c
(
    const short *restrict x,
    const short *restrict h,
    short       *restrict y,
    int                   m,
    int                   x_dim
)
{
    int i, j;

    for (j = 0; j < x_dim - m; j++)
    {
         for (i = 0; i < m; i++)
             y[j] += x[i + j] * h[i];
    }
}

/* ======================================================================== */
/*  End of file:  img_corr_gen.c                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2002 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
