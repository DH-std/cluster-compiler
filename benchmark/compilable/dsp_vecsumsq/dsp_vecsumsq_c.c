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
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_vecsumsq                                                        */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      15-May-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and has the following C prototype:      */
/*                                                                          */
/*          int DSP_vecsumsq                                                */
/*          (                                                               */
/*              const short *x,    // Pointer to vector  //                 */
/*              int          nx    // Length of vector.  //                 */
/*          );                                                              */
/*                                                                          */
/*      This routine returns the sum of squares as its return value.        */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The "DSP_vecsumsq" function returns the sum of squares of the       */
/*      elements contained in vector "x".                                   */
/*                                                                          */
/*  NOTES                                                                   */
/*      This code is ENDIAN NEUTRAL                                         */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

int DSP_vecsumsq_c
(
    const short *x,
    int  count
)
{
    int i;
    int prod, sum = 0;

    for (i = 0; i < count; i++)
    {
        prod = x[i] * x[i];
        sum += prod;
    }

    return sum;
}

/* ======================================================================== */
/*  End of file:  dsp_vecsumsq.c                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
