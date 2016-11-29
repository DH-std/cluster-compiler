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
/*  DESCRIPTION                                                             */
/*      The function pix_sat() takes signed 16-bit input pixels and         */
/*      saturates them to unsigned 8-bit results.  Pixel values above       */
/*      255 are clamped to 255, and values below 0 are clamped to 0.        */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The input must be a multiple of 16 pixels long.                     */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      The input and output data must be double-word aligned.              */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef _PIX_SAT_I_H_
#define _PIX_SAT_I_H_ 1

void pix_sat_c
(
    int n,                            /* Number of pixels */
    const short   *restrict in_data,  /* Incoming data    */
    unsigned char *restrict out_data  /* Outgoing data    */
);

#endif
/* ======================================================================== */
/*  End of file:  pix_sat_i.h                                               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2000 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
