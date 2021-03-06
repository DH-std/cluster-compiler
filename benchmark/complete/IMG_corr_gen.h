/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.13    Sun Sep 29 03:32:19 2002 (UTC)              */
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
/*  Assembler compatibility shim for assembling 4.30 and later code on      */
/*  tools prior to 4.30.                                                    */
/* ======================================================================== */
/* ======================================================================== */
/*  End of assembler compatibility shim.                                    */
/* ======================================================================== */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*          IMG_corr_gen                                                    */
/*                                                                          */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      24-Aug-2001                                                         */
/*                                                                          */
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
/*              Must be word aligned.                                       */
/*      h[M]  : Input 1xM mask array                                        */
/*      y[]   : Output array of correlation sum                             */
/*              Must be double-word aligned.                                */
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
/*  TECHNIQUES                                                              */
/*      It is advisable to software pipeline the loop that is expected to   */
/*      iterate the most number of times. In the case of generalized        */
/*      correlation since the number of filter taps M is not known          */
/*      a priori the loop order interchange optimization is used and the    */
/*      inner and outer loops of the natural C code are exchanged. If the   */
/*      # of taps M is even then it is completely computed by using an      */
/*      optimal 2 tap filter implementation. If M is odd then upto M - 1    */
/*      even taps are computed using the 2 tap filter section and then a    */
/*      1 tap filter section is used for odd tap.                           */
/*                                                                          */
/*      2 tap filter section:                                               */
/*      The 2 tap filter section assumes that the input array is word       */
/*      aligned. In order to minimize the load bandwidth the first word     */
/*      is pre-loaded. Four words are read in and the last read is then     */
/*      moved in as the new data allowing for data re-use. The dotp2        */
/*      instructions allow for the first four even output samples to be     */
/*      computed. Pack instructions then re-align  the input data so that   */
/*      odd samples may be computed without re-loading data using           */
/*      non-aligned loads.                                                  */
/*                                                                          */
/*      1 tap filter case and odd M filter case:                            */
/*      For the 1 tap filter case the code jumps to the start of the 1 tap  */
/*      filter case, and for the odd tap filter case the 2 tap filter       */
/*      section is iterated for as many times as possible and the last odd  */
/*      tap is computed using the 1 tap section.                            */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      Array x[] must be word aligned, array y[ ] must be double-word      */
/*      aligned, and array h[ ] must be half-word aligned.                  */
/*                                                                          */
/*  NOTES                                                                   */
/*      This code is ENDIAN NEUTRAL.                                        */
/*      The code is interrupt-tolerant, but not interruptible.              */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      No bank conflicts occurr.                                           */
/*                                                                          */
/*  CYCLES                                                                  */
/*      when M is even:                                                     */
/*      M * [floor[(x_dim - M + 8)/4] + 11] + 38                            */
/*                                                                          */
/*      when M is odd:                                                      */
/*      (M-1)*[floor[(x_dim - E + 8)/4] + 11] + 3 * (x_dim - E + 4)/4 + 48  */
/*      with E = M + 1                                                      */
/*                                                                          */
/*      For M = 8, x_dim = 720, cycles = 1566                               */
/*      For M = 9, x_dim = 720, cycles = 2102                               */
/*                                                                          */
/*  CODE SIZE                                                               */
/*      636 bytes                                                           */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef IMG_CORR_GEN_H_
#define IMG_CORR_GEN_H_ 1

void IMG_corr_gen
(
    short   *x,
    short   *h,
    short   *y,
    int     m,
    int     x_dim
);

#endif
/* ======================================================================== */
/*  End of file:  img_corr_gen.h                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
