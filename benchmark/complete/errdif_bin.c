/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB  DSP Image/Video Processing Library                              */
/*                                                                          */
/*      Release:        Revision 1.04b                                      */
/*      CVS Revision:   1.2     Mon Jan  7 20:16:00 2002 (UTC)              */
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
/*      IMG_errdif_bin -- Binary Floyd-Steinberg Error Diffusion. Endian Neutral*/
/*                                                                          */
/*  REVISION DATE                                                           */
/*      10-Jul-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and has the following C prototype:      */
/*                                                                          */
/*              void IMG_errdif_bin                                         */
/*              (                                                           */
/*                  unsigned char *restrict errdif_data,                    */
/*                  int           cols,                                     */
/*                  int           rows,                                     */
/*                  short         *restrict err_buf,                        */
/*                  unsigned char thresh                                    */
/*              )                                                           */
/*                                                                          */
/*      errdif_data:     Input/Output image ptr                             */
/*      cols:            Number of columns (Width)                          */
/*      rows:            Number of rows    (Height)                         */
/*      err_buf[cols+1]: Buffer where one row of errors is to be saved      */
/*      thresh:          Threshold in the range [0x00, 0xFF]                */
/*                                                                          */
/*      errdif_data[] is used for both input and output.                    */
/*                                                                          */
/*      err_buf[], additional buffer, should be provided with               */
/*      initialized to all-zero's for the first call with an image.         */
/*      The subsequent call with the same image should provide this         */
/*      kernel the returned err_buf The size of err_buf should be           */
/*      (cols+1)*Half-Word.                                                 */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The code implements the Binary Floyd-Steinberg error diffusion      */
/*      filter.  The filter kernel used is this one:                        */
/*                                                                          */
/*                                  +---+                                   */
/*                                P | 7 |                                   */
/*                          +---+---+---+                                   */
/*                          | 3 | 5 | 1 |                                   */
/*                          +---+---+---+                                   */
/*                                                                          */
/*                                                                          */
/*      Pixels are processed from left-to-right, top-to-bottom.  Each       */
/*      pixel is compared against a user-defined threshold.  Pixels         */
/*      that are larger than the threshold are set to 255, and pixels       */
/*      that are smaller or equal to the threshold are set to 0.  The       */
/*      error value for the pixel (eg. the difference between the           */
/*      thresholded pixel and its original grey level) is propagated to     */
/*      the neighboring pixels according to the filter above.  This         */
/*      error propagation diffuses the error over a larger area, hence      */
/*      the term "error diffusion."                                         */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      The processing of the filter itself is inverted so that the         */
/*      errors from previous pixels "propagate into" a given pixel at       */
/*      the time the pixel is processed, rather than "accumulate into"      */
/*      a pixel as its neighbors are processed.  This allows us to          */
/*      keep our image as an 8-bit image, and reduces the number of         */
/*      accesses to the image array.  The inverted filter kernel            */
/*      performs identically to the kernel's original form.  In this        */
/*      form, the weights specify the weighting assigned to the errors      */
/*      coming from the neighboring pixels.                                 */
/*                                                                          */
/*                          +---+---+---+                                   */
/*                          | 1 | 5 | 3 |                                   */
/*                          +---+---+---+                                   */
/*                          | 7 | P                                         */
/*                          +---+                                           */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      err_buf[] must be initialized to zeros for the first call and       */
/*      the returned err_buf should be provided for the next call.          */
/*                                                                          */
/*  SOURCE                                                                  */
/*      Floyd-Steinberg Error Diffusion.                                    */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2003 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include "IMG_errdif_bin.h"

void IMG_errdif_bin
(
    unsigned char *restrict errdif_data, /* Input/Output image ptr       */
    int           cols,                  /* Number of columns (Width)    */
    int           rows,                  /* Number of rows    (Height)   */
    short         *restrict err_buf,     /* row-to-row error buffer.     */
    unsigned char thresh                 /* Threshold from [0x00, 0xFF]  */
)
{
    int   x, i, y;                /* Loop counters                       */
    int   F;                      /* Current pixel value at [x,y]        */
    int   errA;                   /* Error value at [x-1, y-1]           */
    int   errB;                   /* Error value at [  x, y-1]           */
    int   errC;                   /* Error value at [x+1, y-1]           */
    int   errE;                   /* Error value at [x-1,   y]           */
    int   errF;                   /* Error value at [  x,   y]           */

    /* --------------------------------------------------------- */
    /*  Step through rows of pixels.                             */
    /* --------------------------------------------------------- */
    for (y = 0, i = 0; y < rows; y++)
    {
        /* ----------------------------------------------------- */
        /*  Start off with our initial errors set to zero at the */
        /*  start of the line since we do not have any pixels to */
        /*  the left of the row.  These error terms are          */
        /*  maintained within the inner loop.                    */
        /* ----------------------------------------------------- */
        errA = 0; errE = 0;
        errB = err_buf[0];


        /* ----------------------------------------------------- */
        /*  Step through pixels in each row.                     */
        /* ----------------------------------------------------- */
        for (x = 0; x < cols; x++, i++)
        {
            /* ------------------------------------------------- */
            /*  Load the error being propagated from pixel 'C'   */
            /*  from our error buffer.  This was calculated      */
            /*  during the previous line.                        */
            /* ------------------------------------------------- */
            errC = err_buf[x+1];

            /* ------------------------------------------------- */
            /*  Load our pixel value to quantize.                */
            /* ------------------------------------------------- */
            F = errdif_data[i];

            /* ------------------------------------------------- */
            /*  Calculate our resulting pixel.  If we assume     */
            /*  that this pixel will be set to zero, this also   */
            /*  doubles as our error term.                       */
            /* ------------------------------------------------- */
            errF = F + ((errE*7 + errA + errB*5 + errC*3) >> 4);

            /* ------------------------------------------------- */
            /*  Set pixels that are larger than the threshold to */
            /*  255, and pixels that are smaller than the        */
            /*  threshold to 0.                                  */
            /* ------------------------------------------------- */
            if (errF > thresh)  errdif_data[i] = 0xFF;
            else                errdif_data[i] = 0;

            /* ------------------------------------------------- */
            /*  If the pixel was larger than the threshold, then */
            /*  we need subtract 255 from our error.  In any     */
            /*  case, store the error to the error buffer.       */
            /* ------------------------------------------------- */
            if (errF > thresh)  err_buf[x] = errF = errF - 0xFF;
            else                err_buf[x] = errF;

            /* ------------------------------------------------- */
            /*  Propagate error terms for the next pixel.        */
            /* ------------------------------------------------- */
            errE = errF;
            errA = errB;
            errB = errC;
        }
    }
}

/* ========================================================================= */
/*  End of file:  img_errdif_bin.c                                           */
