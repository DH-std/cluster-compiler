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
/*    TEXAS INSTRUMENTS, INC.                                              */
/*                                                                         */
/*    NAME                                                                 */
/*          DSP_mat_trans                                                  */
/*                                                                         */
/*    REVISION DATE                                                        */
/*        13-May-2001                                                      */
/*                                                                         */
/*  USAGE                                                                  */
/*      This routine is C-callable and can be called as:                   */
/*                                                                         */
/*      void DSP_mat_trans                                                 */
/*      (                                                                  */
/*          const short *restrict x,    // Input matrix            //      */
/*          short rows,                 // Height of input matrix  //      */
/*          short columns,              // Width of input matrix   //      */
/*          short *restrict r           // Output matrix           //      */
/*      );                                                                 */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*      The program transposes a matrix of 16-bit values and user-         */
/*      determined dimensions. The result of a matrix transpose is a       */
/*      matrix with the number of rows = number of columns of input matrix */
/*      and number of columns = number of rows of input matrix The value   */
/*      of an elements of the output matrix is equal to the value of the   */
/*      element from the input matrix with switched coordinates (rows,     */
/*      columns).                                                          */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================= */

void DSP_mat_trans_c
(
    const short *restrict x,
    short rows,
    short columns,
    short *restrict r
)
{
    int i, j;

    #ifdef NOASSUME
    _nassert(columns %4 == 0);
    _nassert(rows % 4 == 0);
    _nassert((int)(x)%8 == 0);
    _nassert((int)(r)%8 == 0);
    _nassert(columns >= 8);
    _nassert(rows >= 8);
    #endif

    /* ------------------------------------------------------------------- */
    /*  Write each column of 'x' to a row of 'r'.                          */
    /* ------------------------------------------------------------------- */
    for (i = 0; i < columns; i++)
        for (j = 0; j < rows; j++)
            r[(i * rows) + j] = x[i + (columns * j)];

}

/* ======================================================================= */
/*  End of file:  dsp_mat_trans.c                                          */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================= */
