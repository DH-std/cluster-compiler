/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      pix_sat                                                             */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and has the following C prototype:      */
/*                                                                          */
/*          void pix_sat                                                    */
/*          (                                                               */
/*              int n,                            // Number of pixels //    */
/*              const short   *restrict in_data,  // Incoming data    //    */
/*              unsigned char *restrict out_data  // Outgoing data    //    */
/*          );                                                              */
/*                                                                          */
/*      This code performs the saturation of 16 bit signed numbers          */
/*      to 8 bit unsigned numbers. If the data is over 255 it is            */
/*      saturated to 255, if it is less than 0 it is saturated to 0.        */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The function pix_sat() takes signed 16-bit input pixels and         */
/*      saturates them to unsigned 8-bit results.  Pixel values above       */
/*      255 are clamped to 255, and values below 0 are clamped to 0.        */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The input must be a multiple of 32 pixels long.                     */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      The input and output data must be double-word aligned.              */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#pragma CODE_SECTION(pix_sat_c,   ".text:intrinsic");
#include <c6x.h>

void pix_sat_c
(
    int                     n,
    const short   *restrict in_data,
    unsigned char *restrict out_data
)
{
    int i;

    if (!n) return;
    _nassert((int) in_data  % 8 == 0);
    _nassert((int) out_data % 8 == 0);

    /* -------------------------------------------------------------------- */
    /*  Process incoming pixels up to 16 at a time.                         */
    /* -------------------------------------------------------------------- */
    #pragma MUST_ITERATE(8,,8);
    #pragma PROB_ITERATE(32);
    #pragma UNROLL(4);
    for (i = 0; i < n; i += 4)
        _amem4(&out_data[i]) = _spacku4(_amem4_const(&in_data[i + 2]),
                                        _amem4_const(&in_data[i + 0]));
}

/* ======================================================================== */
/*  End of file:  pix_sat_i.c                                               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
