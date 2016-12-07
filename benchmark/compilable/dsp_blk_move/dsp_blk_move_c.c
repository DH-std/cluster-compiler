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
/*  NAME                                                                    */
/*      DSP_blk_move -- Move block of memory (overlapping). Endian Neutral  */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      06-Sep-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void DSP_blk_move(short *x, short *r, int nx);                      */
/*                                                                          */
/*          x  --- block of data to be moved                                */
/*          r  --- destination of block of data                             */
/*          nx --- number of elements in block                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Move nx 16-bit elements from one memory location to another.        */
/*      Source and destination may overlap.                                 */
/*                                                                          */
/*      void DSP_blk_move(short *x, short *r, int nx);                      */
/*      {                                                                   */
/*          int i;                                                          */
/*                                                                          */
/*          if (r < x)                                                      */
/*          {                                                               */
/*              for (i = 0 ; i < nx; i++)                                   */
/*                  r[i] = x[i];                                            */
/*          } else                                                          */
/*          {                                                               */
/*              for (i = nx-1 ; i >= 0; i--)                                */
/*                  r[i] = x[i];                                            */
/*          }                                                               */
/*      }                                                                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_blk_move_c(short *x, short *r, int nx)
{
    int i;

    if (r < x)
    {
        for (i = 0; i < nx; i++)
            r[i] = x[i];
    } else
    {
        for (i = nx-1 ; i >= 0; i--)
            r[i] = x[i];
    }
}

/* ======================================================================== */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

