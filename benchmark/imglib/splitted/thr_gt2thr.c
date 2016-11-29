/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.3     Thu Mar 14 07:44:56 2002 (UTC)              */
/*      Snapshot date:  23-Oct-2003                                         */
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
/*      IMG_thr_gt2thr                                                      */
/*                                                                          */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      14-Mar-2002                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine has the following C prototype:                         */
/*                                                                          */
/*      void IMG_thr_gt2thr                                                 */
/*      (                                                                   */
/*          const unsigned char *in_data,     //  Input image data  //      */
/*          unsigned char *restrict out_data, //  Output image data //      */
/*          short cols, short rows,           //  Image dimensions  //      */
/*          unsigned char       threshold     //  Threshold value   //      */
/*      )                                                                   */
/*                                                                          */
/*      This routine performs a thresholding operation on an input          */
/*      image in in_data[] whose dimensions are given in the arguments      */
/*      'cols' and 'rows'.  The thresholded pixels are written to the       */
/*      output image pointed to by out_data[].  The input and output        */
/*      are exactly the same dimensions.                                    */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Pixels that are above the threshold value are written to the        */
/*      output unmodified.  Pixels that are greater than the threshold      */
/*      are set to the threshold value in the output image.                 */
/*                                                                          */
/*      The exact thresholding function performed is described by           */
/*      the following transfer function diagram:                            */
/*                                                                          */
/*                                                                          */
/*                 255_|                                                    */
/*                     |                                                    */
/*                     |                                                    */
/*            O        |                                                    */
/*            U        |                                                    */
/*            T    th _|. . . . . _________                                 */
/*            P        |        /.                                          */
/*            U        |      /  .                                          */
/*            T        |    /    .                                          */
/*                     |  /      .                                          */
/*                   0_|/________.__________                                */
/*                     |         |        |                                 */
/*                     0        th       255                                */
/*                                                                          */
/*                             INPUT                                        */
/*                                                                          */
/*      Please see the IMGLIB functions IMG_thr_le2thr, IMG_thr_gt2max      */
/*      and IMG_thr_le2min for other thresholding functions.                */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The input and output buffers do not alias.                          */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      This code is ENDIAN NEUTRAL.                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

void IMG_thr_gt2thr
(
    const unsigned char *in_data,                /*  Input image data    */
    unsigned char       *restrict out_data,      /*  Output image data   */
    short cols, short rows,                      /*  Image dimensions    */
    unsigned char       threshold                /*  Threshold value     */
)
{
    int i, pixels = rows * cols;

    /* -------------------------------------------------------------------- */
    /*  Step through input image copying pixels to the output.  If the      */
    /*  pixels are above our threshold, set them to the threshold value.    */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < pixels; i++)
        out_data[i] = in_data[i] > threshold ? threshold : in_data[i];
}

/* ======================================================================== */
/*  End of file:  img_thr_gt2thr.c                                          */
