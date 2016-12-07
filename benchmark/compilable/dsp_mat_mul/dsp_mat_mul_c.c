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
/*      DSP_mat_mul -- Matrix Multiply                                      */
/*                                                                          */
/*   REVISION DATE                                                          */
/*       13-Jan-2002                                                        */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void DSP_mat_mul                                                */
/*          (                                                               */
/*              const short *restrict x, int r1, int c1,                    */
/*              const short *restrict y,         int c2,                    */
/*              short       *restrict r,                                    */
/*              int                   qs                                    */
/*          );                                                              */
/*                                                                          */
/*      x  == Pointer to r1 by c1 input matrix.                             */
/*      y  == Pointer to c1 by c2 input matrix.                             */
/*      r  == Pointer to r1 by c2 output matrix.                            */
/*                                                                          */
/*      r1 == Number of rows in x.                                          */
/*      c1 == Number of columns in x.  Also number of rows in y.            */
/*      c2 == Number of columns in y.                                       */
/*                                                                          */
/*      qs == Final right-shift to apply to the result.                     */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This function computes the expression "r = x * y" for the           */
/*      matrices x and y.  The columnar dimension of x must match           */
/*      the row dimension of y.  The resulting matrix has the same          */
/*      number of rows as x and the same number of columns as y.            */
/*                                                                          */
/*      The values stored in the matrices are assumed to be fixed-point     */
/*      or integer values.  All intermediate sums are retained to 32-bit    */
/*      precision, and no overflow checking is performed.  The results      */
/*      are right-shifted by a user-specified amount, and then truncated    */
/*      to 16 bits.                                                         */
/*                                                                          */
/*      This code is suitable for dense matrices.  No optimizations are     */
/*      made for sparse matrices.                                           */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The arrays 'x', 'y', and 'r' are stored in distinct arrays.  That   */
/*      is, in-place processing is not allowed.                             */
/*                                                                          */
/*      The input matrices have minimum dimensions of at least 1 row and    */
/*      1 column, and no more than 32767 rows or 32767 columns.             */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_mat_mul_c
(
    const short *restrict x, int r1, int c1,
    const short *restrict y,         int c2,
    short       *restrict r,
    int                   qs
)
{
    int i, j, k;
    int sum;

    /* -------------------------------------------------------------------- */
    /*  Multiply each row in x by each column in y.  The product of row m   */
    /*  in x and column n in y is placed in position (m,n) in the result.   */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++)
        {
            sum = 0;
            for (k = 0; k < c1; k++)
                sum += x[k + i*c1] * y[j + k*c2];

            r[j + i*c2] = sum >> qs;
        }
}
/* ======================================================================== */
/*  End of file:  dsp_mat_mul.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
