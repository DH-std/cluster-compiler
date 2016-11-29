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
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_maxval                                                          */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      18-Sep-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*         short DSP_maxval(const short *x, int nx);                        */
/*                                                                          */
/*         x  = address to array of values                                  */
/*         nx = number of values in array                                   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine finds the maximum value of a vector and returns        */
/*      the value.                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

short DSP_maxval_c(const short *x, int nx)
{
    int i;
    short max = -32768;

    /* -------------------------------------------------------------------- */
    /*  Determine the maximum, value in the given vector and return it.     */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < nx; i++)
        if (x[i] > max)
            max = x[i];

    return max;

}

/* ======================================================================== */
/*  End of file:  dsp_maxval.c                                              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
