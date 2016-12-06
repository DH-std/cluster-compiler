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
/*      DSP_minval                                                          */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      18-Sep-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*         short DSP_minval(const short *x, int nx);                        */
/*                                                                          */
/*         x  = address to array of values                                  */
/*         nx = number of values in array                                   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine finds the minimum value of a vector and returns        */
/*      the value.                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

short DSP_minval_c(const short *x, int nx)
{
    int i;
    short min = 32767;

    /* -------------------------------------------------------------------- */
    /*  Determine the minimum, value in the given vector and return it.     */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < nx; i++)
        if (x[i] < min)
            min = x[i];

    return min;

}

/* ======================================================================== */
/*  End of file:  dsp_minval.c                                              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
