q15tofl.c/      1066929506  0     0     0       5747      `
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.3     Mon Mar 11 20:57:07 2002 (UTC)              */
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
/*      DSP_q15tofl -- Q.15 to IEEE float conversion                        */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      17-Jul-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void DSP_q15tofl (short *x, float *r, int nx)                   */
/*                                                                          */
/*          x[nx]  ---  Pointer to Q15 input vector of size nx              */
/*          r[nx]  ---  Pointer to floating-point output data vector        */
/*                      of size nx containing the floating-point equivalent */
/*                      of vector input                                     */
/*          nx     ---  length of input and output data vectors             */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Converts the Q15 stored in vector input to IEEE floating point      */
/*      numbers stored in vector output.                                    */
/*                                                                          */
/*      void DSP_q15tofl (short *x, float *r, int nx)                       */
/*      {                                                                   */
/*       int i;                                                             */
/*                                                                          */
/*       for (i=0;i<nx;i++)                                                 */
/*            r[i]=(float)x[i]/0x8000;                                      */
/*      }                                                                   */
/*                                                                          */
/*      The above C code is a general implementation without                */
/*      restrictions.  The assembly code may have some restrictions, as     */
/*      noted below.                                                        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_q15tofl(const short *restrict x, float *r, int nx )
{
    int i;

    for (i=0;i<nx;i++)
        r[i]=(float)x[i]/32768;
}

/* ======================================================================== */
/*  End of file:  dsp_q15tofl.c                                             */
