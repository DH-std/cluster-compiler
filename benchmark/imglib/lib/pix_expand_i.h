/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      pix_expand                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void pix_expand                                                     */
/*      (                                                                   */
/*          int n,                                    // # of elements //   */
/*          const unsigned char *restrict in_data,    // Input data    //   */
/*          short               *restrict out_data    // Output data   //   */
/*      )                                                                   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Reads an array of unsigned 8-bit values and store them to a         */
/*      16-bit array.  This step is often used as the first step            */
/*      when processing pixels or other low-precision data at 16-bit        */
/*      intermediate precision.                                             */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef _PIX_EXPAND_I_H
#define _PIX_EXPAND_I_H 1

void pix_expand_c
(
    int n,
    const unsigned char *restrict ip,
    short               *restrict op
);

#endif
/* ======================================================================== */
/*  End of file:  pix_expand_i.h                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
