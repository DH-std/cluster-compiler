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
/*                                                                          */
/*   TEXAS INSTRUMENTS, INC.                                                */
/*                                                                          */
/*   NAME                                                                   */
/*         DSP_dotp_sqr                                                     */
/*                                                                          */
/*   REVISION DATE                                                          */
/*       29-Mar-2002                                                        */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and can be called as:                   */
/*                                                                          */
/*          int DSP_dotp_sqr                                                */
/*          (                                                               */
/*              int G,            // Sum-of-y-squared initial value //      */
/*              const short  *x,  // First input array.             //      */
/*              const short  *y,  // Second input array.            //      */
/*              int *restrict r,  // Accumulation of x[] * y[].     //      */
/*              int nx            // Length of the input vector.    //      */
/*          );                                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine computes the dot product of x[] and y[] arrays,        */
/*      adding it to the value in the location pointed to by 'd'.           */
/*                                                                          */
/*      Additionally, it computes the sum of the squares of the terms       */
/*      in the y[] array, adding it to the argument G.  The final value     */
/*      of G is given as the return value of the function.  This value      */
/*      is used by the VSELP vocoder.                                       */
/*                                                                          */
/*      The following C code is an implementation of the algorithm          */
/*      without restrictions.  Optimized implementations may add            */
/*      restrictions as noted under the heading "ASSUMPTIONS."              */
/*                                                                          */
/*      int DSP_dotp_sqr                                                    */
/*      (                                                                   */
/*          int G,            // Sum-of-y-squared initial value //          */
/*          const short  *x,  // First input array.             //          */
/*          const short  *y,  // Second input array.            //          */
/*          int *restrict r,  // Accumulation of x[] * y[].     //          */
/*          int nx            // Length of the input vector.    //          */
/*      )                                                                   */
/*      {                                                                   */
/*          int i;                                                          */
/*                                                                          */
/*          for (i = 0; i < nx; i++)                                        */
/*          {                                                               */
/*              *r += x[i] * y[i];                                          */
/*              G  += y[i] * y[i];                                          */
/*          }                                                               */
/*                                                                          */
/*          return G;                                                       */
/*      }                                                                   */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      This code is ENDIAN NEUTRAL.                                        */
/*                                                                          */
/*                                                                          */
/*  SOURCE                                                                  */
/*      DSPLIB.                                                             */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

int DSP_dotp_sqr_c
(
    int G,
    const short  *x,
    const short  *y,
    int *restrict r,
    int nx
)
{
    int i;

    for (i = 0; i < nx; i++)
    {
        *r += x[i] * y[i];
        G  += y[i] * y[i];
    }

    return G;
}

/* ======================================================================== */
/*  End of file:  dsp_dotp_sqr.c                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
