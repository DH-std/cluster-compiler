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
/*      DSP_recip16                                                         */
/*                                                                          */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      20-Jul-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void DSP_recip16 (short *x, short *rfrac, short *rexp, short nx);   */
/*                                                                          */
/*      x[nx]     = Pointer to input vector of size nx                      */
/*      rfrac[nx] = Pointer to output vector of size nx to                  */
/*                  contain the fractional part of the reciprocal           */
/*      rexp[nx]  = Pointer to output vector of size nx to                  */
/*                  contain the exponent part of the reciprocal             */
/*      nx        = Number of elements in input vector                      */
/*                                                                          */
/*      (See the C compiler reference guide.)                               */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This program performs a reciprocal on a vector of Q15 numbers.      */
/*      The result is stored in two parts: a Q15 part and an exponent       */
/*      (power of two) of the fraction.                                     */
/*      First, the input is loaded, then its absolute value is taken,       */
/*      then it is normalized, then divided using a loop of conditional     */
/*      subtracts, and finally it is negated if the original input was      */
/*      negative.                                                           */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void DSP_recip16_c (short *x, short *rfrac, short *rexp, short nx)
{
   int i,j,a,b;
   short neg, normal;

   for(i = nx; i > 0; i--)
   {
       a = *(x++);
       if(a < 0)             /* take absolute value */
       {
           a = -a;
           neg = 1;
       }
       else
           neg = 0;

       normal = _norm(a);              /* normalize */
       a = a << normal;

       *(rexp++) = normal - 15;   /* store exponent */
       b = 0x80000000;              /* dividend = 1 */

       for(j = 15; j > 0; j--)
           b = _subc(b,a);                /* divide */

       b = b & 0x7FFF;           /* clear remainder */

       if(neg) b = -b;       /* if negative, negate */

       *(rfrac++) = b;            /* store fraction */
   }
}
/* ======================================================================== */
/*  End of file:  dsp_recip16.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
