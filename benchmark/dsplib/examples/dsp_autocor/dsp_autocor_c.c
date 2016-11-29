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
/*      DSP_autocor -- Autocorrelation                                     */
/*                                                                         */
/*  REVISION DATE                                                          */
/*      21-Jan-2002                                                        */
/*                                                                         */
/*  USAGE                                                                   */
/*      This routine has the following C prototype:                         */
/*                                                                          */
/*      void DSP_autocor                                                    */
/*      (                                                                   */
/*          short *restrict r,                                              */
/*          const short *restrict x,                                        */
/*          int          nx,                                                */
/*          int          nr                                                 */
/*      );                                                                  */
/*                                                                          */
/*      r[nr]   : Output array                                              */
/*      x[nr+nx]: Input array. The first nr elements are assumed to be 0.   */
/*      nx      : Length of autocorrelation                                 */
/*      nr      : Number of lags                                            */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine performs an autocorrelation of an input vector         */
/*      x. The length of the autocorrelation is nx samples. Since nr        */
/*      such autocorrelations are performed, input vector x needs to be     */
/*      of length nx + nr. This produces nr output results which are        */
/*      stored in an output array r.                                        */
/*                                                                          */
/*      The following diagram illustrates how the correlations are          */
/*      obtained.                                                           */
/*                                                                          */
/*      Example for nr=8, nx=24:                                            */
/*      0       nr                  nx+nr-1                                 */
/*      |-------|----------------------|  <- x[]                            */
/*      |       |----------------------|  -> r[0]                           */
/*      |      |----------------------|   -> r[1]                           */
/*      |     |----------------------|    -> r[2]                           */
/*      |    |----------------------|     -> r[3]                           */
/*      |   |----------------------|      -> r[4]                           */
/*      |  |----------------------|       -> r[5]                           */
/*      | |----------------------|        -> r[6]                           */
/*                                                                          */
/*      Note that x[0] is never used, but is required for padding to make   */
/*      x[nr] double-word aligned.                                          */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The first nr elements are assumed to be 0.                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_autocor_c(short *restrict r, const short *restrict x, int nx, int nr)
{
   int i, k;
   int sum;

   #ifndef NOASSUME
   _nassert (nr % 4 == 0);
   #endif

   /*----------------------------------------------------------------------*/
   /* Outer loop that iterates for every output. There are 'nr' output     */
   /* samples to be computed. Hence this loop iterates 'nr' times. 'nr'    */
   /* needs to be a multiple of 4. This information is conveyed to the     */
   /* compiler.                                                            */
   /*----------------------------------------------------------------------*/

   for (i = 0; i < nr; i++)
   {
      sum = 0;

      #ifndef NOASSUME
      _nassert(nx % 8 == 0);
      _nassert((int)(x)%8 == 0);
      _nassert((int)(r)%8 == 8);
      _nassert(nr%2 == 0);
      #pragma MUST_ITERATE(10, ,2);
      #endif

      /*-------------------------------------------------------------------*/
      /*  Compute one autocorrelation. Each autocorrelation has 'nx' terms */
      /*  'nx' is assumed to be a multiple of 8.                           */
      /*-------------------------------------------------------------------*/

      for (k = nr; k < nx + nr; k++)
      {
          sum += x[k] * x[k-i];
      }

      /*-------------------------------------------------------------------*/
      /* Shift out autocorrelation sum taking into account Q15 math.       */
      /*-------------------------------------------------------------------*/

      r[i] = sum  >> 15;
   }
}

/* ======================================================================== */
/*  End of file:  dsp_autocor.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
