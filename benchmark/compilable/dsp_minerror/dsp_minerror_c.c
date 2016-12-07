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
/*                                                                         */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_minerror --  Minimum Energy Error Search                       */
/*S                                                                        */
/*                                                                         */
/*  REVISION DATE                                                          */
/*      11-Feb-2002                                                        */
/*                                                                         */
/*  USAGE                                                                  */
/*      This routine is C-callable and can be called as:                   */
/*                                                                         */
/*      int DSP_minerror                                                   */
/*      (                                                                  */
/*          const short *restrict GSP0_TABLE,                              */
/*          const short *restrict errCoefs,                                */
/*          int         *restrict max_index                                */
/*      );                                                                 */
/*                                                                         */
/*      GSP0_TABLE[256*9] :  Pointer to GSP0 terms array.                  */
/*                           Must be double-word aligned.                  */
/*      errCoefs[9]       :  Array of error coefficients.                  */
/*      max_index         :  Index to GSP0_TABLE[max_index], the first     */
/*                           element of the 9-element vector that resulted */
/*                           in the maximum dot product.                   */
/*      return int        :  Maximum dot product result.                   */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*      Performs a dot product on 256 pairs of 9 element vectors and       */
/*      searches for the pair of vectors which produces the maximum dot    */
/*      product result. This is a large part of the VSELP vocoder codebook */
/*      search.                                                            */
/*                                                                         */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================= */

#define GSP0_TERMS 9
#define GSP0_NUM 256

int DSP_minerror_c
(
        const short *restrict GSP0_TABLE,
        const short *restrict errCoefs,
        int *max_index
)
{
    int val, maxVal = -50;
    int i, j;

    for (i = 0; i < GSP0_NUM; i++)
    {
        for (val = 0, j = 0; j < GSP0_TERMS; j++)
           val += GSP0_TABLE[i*GSP0_TERMS+j] * errCoefs[j];

        if (val > maxVal)
        {
           maxVal = val;
           *max_index = i*GSP0_TERMS;
        }
    }

    return (maxVal);
}

/* ========================================================================== */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ========================================================================== */
