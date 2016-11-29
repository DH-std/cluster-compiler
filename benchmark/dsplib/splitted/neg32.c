neg32.c/        1066929506  0     0     0       5565      `
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.4     Mon Dec 10 20:54:20 2001 (UTC)              */
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
/*                                                                          */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_neg32                                                           */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      10-Dec-2001                                                         */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and may be called using the following   */
/*      C function prototype:                                               */
/*                                                                          */
/*          void DSP_neg32                                                  */
/*          (                                                               */
/*              int   *x,      // Input data array     //                   */
/*              int   *r,      // Output data array    //                   */
/*              short nx       // Number of elements.  //                   */
/*          );                                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine negates an array of 32-bit integers, and stores        */
/*      the result either in a new array, or back to the same array.        */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      This kernel is ENDIAN NEUTRAL.                                      */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The input must be at least 8 elements long, and a multiple of 4.    */
/*                                                                          */
/*      The input and output arrays must not overlap, except in the         */
/*      special case where the input and output pointers are exactly        */
/*      equal.                                                              */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_neg32(int *x, int *r, short nx)
{
    int i;

    for (i = 0; i < nx; i++)
          r[i] = -x[i];
}

/* ======================================================================== */
/*   End of file:  dsp_neg32.c                                              */
